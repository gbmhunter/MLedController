//!
//! @file				LedController.hpp
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
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef M_LED_CONTROLLER_LED_CONTROLLER_H
#define M_LED_CONTROLLER_LED_CONTROLLER_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	struct LedWakeupEntry;
	class LedController;
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
#include <cstdint>		// uint8_t, uint32_t, e.t.c

//! @debug
#include <iostream>

//===== USER LIBRARIES =====//
#include "MHal/api/MHalApi.hpp"
#include "MOsal/api/MOsalApi.hpp"
#include "MVector/api/MVectorApi.hpp"	// MVector
#include "MList/api/MListApi.hpp"		// List, Iterator

//===== USER SOURCE =====//
#include "Led.hpp"

namespace MbeddedNinja
{

	struct LedWakeupEntry
	{
		Led * led;
		double wakeUpTimeMs;
	};

	class LedController
	{

		public:

		friend class Led;

		//! @brief		Constructor.
		LedController(MOsalNs::Osal * osal, MOsalNs::Thread * thread);

		//! @brief		Starts the LED controller thread.
		void Start();

		//! @brief		Stops the LED controller thread.
		void Stop();

		//! @brief		The method the LED controller thread will run.
		void ThreadMethod(bool dummy);

		//! @brief		Registers an LED object with the LED controller.
		//! @details	The LED object must remain valid for the entire time it is registered with the LED controller.
		//! @param		led		The LED object to register.
		//! @note		Thread-safe.
		void RegisterLed(
			Led * led);

		void DeleteLed(
			Led * led);

		//! @brief		Automatically called by LED objects to inform the LED controller when their state changes.
		//! @note		Thread-safe.
		void LedStateChanged(Led * led);

		private:

		void OrderedInsert(LedWakeupEntry ledWakeupEntry);

		//! @brief		The thread object for the LED controller. This runs ThreadMethod().
		MOsalNs::Thread * thread;

		//! @brief		The operating system abstraction layer provided to the LED controller through the constructor.
		MOsalNs::Osal * osal;

		//! @brief		A vector to keep track of all the registered LEDs.
		MVector<Led*> ledV;

		//! @brief		A doubly-linked list to keep track of all the future wake-up times.
		//! @details	This will have to hold an object which contains both the wake-up times and the relevant LED object.
		List<LedWakeupEntry> wakeUpTimesMs;


	};


} // namespace MbeddedNinja

#endif	// #ifndef M_LED_CONTROLLER_LED_CONTROLLER_H

// EOF
