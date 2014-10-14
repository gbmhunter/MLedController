//!
//! @file				LedController.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-10-13
//! @last-modified		2014-10-14
//! @brief
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

//===== USER SOURCE =====//
#include "Led.hpp"

namespace MbeddedNinja
{

	class LedController
	{

		public:

		LedController(MOsalNs::Osal * osal, MOsalNs::Thread * thread)
		{
			MCallbacks::CallbackGen<LedController, void, bool> myCallback(this, &LedController::ThreadMethod);
			thread->AssignThreadMethod(myCallback);
			this->thread = thread;
			this->osal = osal;
		}

		void Start()
		{
			this->thread->Start();
		}

		void Stop()
		{
			this->thread->Stop();
		}

		void ThreadMethod(bool dummy);

		//! @brief		Registers an LED object with the LED controller.
		//! @details	The LED object must remain valid for the entire time it is registered with the LED controller.
		void RegisterLed(
			Led * led)
		{
			// Remember the LED by storing it's pointer into the
			// LED vector
			ledV.Append(led);
		}

		void DeleteLed(
			Led * led);

		MOsalNs::Thread * thread;
		MOsalNs::Osal * osal;

		//! @brief		A vector to keep track of all the registered LEDs.
		MVector<Led*> ledV;


	};


} // namespace MbeddedNinja

#endif	// #ifndef M_LED_CONTROLLER_LED_CONTROLLER_H

// EOF
