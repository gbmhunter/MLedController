//!
//! @file				LedController.cpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-10-13
//! @last-modified		2014-10-24
//! @brief				A thread-based LED controller that is responsible for flashing LEDs that have been registered to it.
//! @details
//!						See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
#include <cstdint>		// int8_t, int32_t e.t.c
#include <cstring>		// strlen(), strncpy()
#include <cstdio>		// snprintf()
#include <cinttypes>	// PRId8, PRId32, e.t.c
//#include <iostream>		//!< @debug

//===== USER LIBRARIES =====//
// none

//===== USER SOURCE =====//
#include "../include/LedController.hpp"


namespace MbeddedNinja
{

	LedController::LedController(MOsalNs::Osal * osal, MOsalNs::Thread * thread)
	{
		MCallbacks::CallbackGen<LedController, void, bool> myCallback(this, &LedController::ThreadMethod);
		thread->AssignThreadMethod(myCallback);
		this->thread = thread;
		this->osal = osal;
	}

	void LedController::ThreadMethod(bool dummy)
	{
		std::cout << "Thread method running." << std::endl;

		LedWakeupEntry nextLedEntryToWakeupFor;

		while(!this->thread->stopThread)
		{

			// This has to be inside a mutex that protects the linked list!

			// Get the current time, this will serve as the current time stamp for the rest of the method
			// (do NOT call GetTimeMs() again to get an updated version!)
			double currTime = this->osal->GetTimeMs();

			std::cout << "Current time = '" << currTime << "'." << std::endl;

			/*
			for(uint32_t x = 0; x < this->ledV.Size(); x++)
			{
				std::cout << "LED registered!" << std::endl;
			}*/

			// Iterate through each wakeup entry in the list
			List<LedWakeupEntry>::Iterator it;
			for(it = this->wakeUpTimesMs.Start(); it != this->wakeUpTimesMs.End(); it++)
			{
				std::cout << "Led = '" << (*it).led << "'. Wakeup time = '" << (*it).wakeUpTimeMs << "'." << std::endl;

				// Check to see if the currently inspected led wakeup time has elapsed
				if((*it).wakeUpTimeMs <= currTime)
				{
					// Currently inspected LED needs attention!

					// Remember led
					Led * led = (*it).led;

					led->gpio->Write(0);

					// Remove from list
					this->wakeUpTimesMs.Delete(it);

					// Add new entry for the future
					double wakeUpTimeMs = currTime + led->flashPeriodMs;

					LedWakeupEntry ledWakeupEntry;
					ledWakeupEntry.led = led;
					ledWakeupEntry.wakeUpTimeMs = wakeUpTimeMs;
					// This needs to be added at the correct location!
					this->OrderedInsert(ledWakeupEntry);
				}
			}

			// We now have to get the next thing we need to wake up for

			nextLedEntryToWakeupFor = *this->wakeUpTimesMs.Start();
			double timeToDelay = nextLedEntryToWakeupFor.wakeUpTimeMs - currTime;

			std::cout << "Delaying thread for '" << timeToDelay << "ms'." << std::endl;

			// Delay before re-processing LEDs. The delay is going to be set dynamically!
			this->osal->ThreadDelayMs(timeToDelay);
		}

		std::cout << "Thread exiting." << std::endl;
	}

	void LedController::OrderedInsert(LedWakeupEntry ledWakeupEntry)
	{
		List<LedWakeupEntry>::Iterator it;
		for(it = this->wakeUpTimesMs.Start(); it != this->wakeUpTimesMs.End(); it++)
		{
			if(ledWakeupEntry.wakeUpTimeMs < (*it).wakeUpTimeMs)
			{
				// Insert before the current node pointed to by the iterator
				this->wakeUpTimesMs.Insert(it, ledWakeupEntry);
			}

		}

		this->wakeUpTimesMs.Insert(it, ledWakeupEntry);
	}

	void LedController::Start()
	{
		this->thread->Start();
	}

	void LedController::Stop(){
		this->thread->Stop();
	}

	void LedController::RegisterLed(
		Led * led)
	{
		// This will have to be thread-safe!!!

		// Remember the LED by storing it's pointer into the
		// LED vector
		ledV.Append(led);

		// The LED also needs to know if and what LED controller it is registered to.
		led->ledController = this;
	}

	void LedController::LedStateChanged(Led * led)
	{
		// This will have to be thread-safe!!!

		if(led->ledState == Led::LedStates::FLASHING)
		{
			LedWakeupEntry ledWakeUpEntry;
			ledWakeUpEntry.led = led;
			// We want to set the time to be in the future
			ledWakeUpEntry.wakeUpTimeMs = this->osal->GetTimeMs() + led->flashPeriodMs;

			List<LedWakeupEntry>::Iterator it;
			for(it = this->wakeUpTimesMs.Start(); it != this->wakeUpTimesMs.End(); it++)
			{
				// Check to see whether the provided flash time is less than the current node
				if(led->flashPeriodMs < (*it).wakeUpTimeMs)
				{
					// Insert data into list before the current node
					this->wakeUpTimesMs.Insert(it, ledWakeUpEntry);
					// Lets exit
					return;
				}
			}

			// If we get here, provided flash time is larger than all nodes currently in list (or list
			// is empty), and the iterator will be at the end of the list, so let's insert it here
			this->wakeUpTimesMs.Insert(it, ledWakeUpEntry);
		}


	}


} // namespace MbeddedNinja

// EOF
