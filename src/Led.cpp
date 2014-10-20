//!
//! @file				Led.cpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-10-16
//! @last-modified		2014-10-16
//! @brief				A LED object which can be created by the user when they want to control an LED.
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
#include "../include/Led.hpp"

namespace MbeddedNinja
{

	void Led::Flash(double periodMs)
	{
		// Make sure the LED has been registered to a LED controller!
		M_ASSERT(this->ledController);

		// Set the LED state to flashing
		this->ledState = LedStates::FLASHING;

		// Remember the flash period
		this->flashPeriodMs = periodMs;

		// Inform the LED controller the LED state has changed
		this->ledController->LedStateChanged(this);
	}

} // namespace MbeddedNinja

// EOF
