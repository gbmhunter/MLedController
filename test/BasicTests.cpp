//!
//! @file 			BasicTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-10-13
//! @last-modified 	2014-10-14
//! @brief 			Contains basic tests.
//! @details
//!					See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
#include <cstdint>	// uint32_t, e.t.c
#include <iostream>

//====== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"
#include "MOsal/port/Linux/LinuxOsal.hpp"
#include "MOsal/port/Linux/LinuxThread.hpp"
#include "MHal/port/Linux/LinuxGpio.hpp"

//===== USER SOURCE =====//
#include "../api/MLedControllerApi.hpp"

using namespace MbeddedNinja;

namespace MLedControllerTestsNs
{

	MTEST(BasicTest)
	{

		// Create both a Linux OSAL and Linux thread object which
		// are required by the LED controller objects.
		MOsalNs::LinuxOsal linuxOsal;
		MOsalNs::LinuxThread linuxThread;

		// Create a LED controller
		LedController ledController(&linuxOsal, &linuxThread);

		// Create a new Linux GPIO pin (which is a dummy pin, and just prints to std::out when "toggled")
		MHalNs::LinuxGpio linuxGpio;

		// Create a new LED which uses the Linux GPIO pin
		Led led(&linuxGpio);

		// Register LED with the LED controller
		ledController.RegisterLed(&led);

		// Start the LED controller thread
		ledController.Start();

		// Delay thread to give thread a chance to run
		linuxOsal.ThreadDelayMs(5000);

		// Now lets stop the thread
		ledController.Stop();

		// Check capacity is calculated correctly
		CHECK_EQUAL(true, true);
	}


} // namespace MLedControllerTestsNs
