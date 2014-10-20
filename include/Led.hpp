//!
//! @file				Led.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-10-14
//! @last-modified		2014-10-20
//! @brief				A LED object which can be created by the user when they want to control an LED.
//! @details
//!						See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef M_LED_CONTROLLER_LED_H
#define M_LED_CONTROLLER_LED_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	class Led;
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
#include "LedController.hpp"

namespace MbeddedNinja
{

	//! @brief
	//! @details	Exceptions are not used.
	class Led
	{	
		
		public:

		friend class LedController;


		enum class LedStates
		{
			OFF,
			FLASHING
		};

		//======================================================================================//
		//==================================== PUBLIC METHODS ==================================//
		//======================================================================================//

		//! @brief		Constructor.
		//! @details
		Led(MHalNs::Gpio * gpio) :
			gpio(gpio),
			ledController(nullptr),
			ledState(LedStates::OFF),
			flashPeriodMs(0.0)
		{}

		void Flash(double periodMs);

		void StopFlashing();
				
		private:

		//! @brief		Pointer to the GPIO object the LED will use to control the LED.
		//! @details	Assigned to in the LED's constructor.
		MHalNs::Gpio * gpio;

		//! @brief		This keeps track of what LED controller the LED is registered to (will be = to nullptr if LED is not registered).
		//! @details	The LED object needs to know this so that when you change the LED state, it can inform the controller it is registered to. Assigned to when you call LedController::RegisterLed().
		LedController * ledController;


		LedStates ledState;

		//! @brief		Remembers the flash period (in milliseconds) provided to Flash().
		double flashPeriodMs;

	}; // class Led


} // namespace MbeddedNinja

#endif	// #ifndef M_LED_CONTROLLER_LED_H

// EOF
