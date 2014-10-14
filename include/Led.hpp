//!
//! @file				Led.hpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2014-10-14
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


namespace MbeddedNinja
{

	//! @brief
	//! @details	Exceptions are not used.
	class Led
	{	
		
		public:


		enum class FlashStates
		{
			OFF

		};

		//======================================================================================//
		//==================================== PUBLIC METHODS ==================================//
		//======================================================================================//



		//! @brief		Constructor.
		//! @details
		Led(MHalNs::Gpio * gpio)
		{
			this->gpio = gpio;
		}

		void Flash(double periodMs);

		void StopFlashing();
				
		private:

		MHalNs::Gpio * gpio;
						

		protected:


			// none
		
	}; // class Led


} // namespace MbeddedNinja

#endif	// #ifndef M_LED_CONTROLLER_LED_H

// EOF
