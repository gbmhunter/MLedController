//!
//! @file				LedController.cpp
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


	void LedController::ThreadMethod(bool dummy)
	{
		std::cout << "Thread method running." << std::endl;

		while(!this->thread->stopThread)
		{
			for(uint32_t x = 0; x < this->ledV.Size(); x++)
			{
				std::cout << "LED registered!" << std::endl;
			}
			// Delay before re-processing LEDs
			this->osal->ThreadDelayMs(1000);
		}

		std::cout << "Thread exiting." << std::endl;
	}


} // namespace MbeddedNinja

// EOF
