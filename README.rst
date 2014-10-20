==============
MLedController
==============

---------------------------------------------------------------------------------------------
A microcontroller friendly C++ module to flash your LEDs (and other things).
---------------------------------------------------------------------------------------------

.. image:: https://api.travis-ci.org/mbedded-ninja/MLedController.png?branch=master   
	:target: https://travis-ci.org/mbedded-ninja/MLedController

- Author: gbmhunter <gbmhunter@gmail.com> (www.mbedded.ninja)
- First Ever Commit: 2014-10-13
- Last Modified: 2014-10-20
- Version: v1.1.0.0
- Company: mbedded.ninja
- Project: MToolkit Module
- Language: C++
- Compiler: GCC	
- uC Model: n/a
- Computer Architecture: n/a
- Operating System: n/a
- Documentation Format: Doxygen
- License: GPLv3

Description
===========

In a multi-threaded embedded environment, LEDs are easy to turn on and off. They start to become problematic when you want to flash them or add any other complex control logic. How do you flash them without stalling a thread? How do you flash them without creating many different states for each LED? MLedController takes care of this by providing a tidy, powerful and non-interferring module for controlling LEDs. 

The idea is simple, MLedController has an LedController object and one or more Leds objects. The LedController runs it's own thread, provided by the operating-system abstraction layer MOsal. The user creates Leds (which get associated with a GPIO pin, provided by the hardware abstraction layer MHal) from any thread and registers them to the LedController. When the user sets the LED to a flashing state (or similar), the LED object notifies the LedController and the LedController remembers when it needs to wakeup and change the state of the GPIO pin associated with the LED.

Features:

- Embedded (microcontroller) support
- Small flash/RAM memory footprint (no depedance on the C++ standard library)
- Unit tests
- Doxygen-style well-documented API.
- Portability
	

Code Dependencies
=================

The following table lists all of MStrings dependencies.

====================== ==================== ======================================================================
Dependency             Delivery             Usage
====================== ==================== ======================================================================
MAssert                External module      Providing runtime safety checks against this module.
MHal                   External module      Abstraction layer for the hardware GPIO pins to control the LEDs.
MList                  External module      Doubly-linked list container for keeping track of LedController wake-up times.
MOsal                  External module      Abstraction layer that provides OS objects (e.g. threads and delays).
MUnitTest              External module      Framework for unit tests.
====================== ==================== ======================================================================

Issues
======

See GitHub Issues.

Limitations
===========

Nothing here yet.

Usage
=====

See the unit tests in the 'test/' directory for basic examples.
	
Changelog
=========

========= ========== ===================================================================================================
Version   Date       Comment
========= ========== ===================================================================================================
v1.1.0.0  2014-10-20 Fixed module name in README, closes #2. Add MOsal to the list of dependencies listed in the README, closes #3. Added a better description about MLedController to the README. Added MList as a dependency of this module. Add functionality so that an LED can be flashed at an arbitrary flash rate, closes #1.
v1.0.0.0  2014-10-14 Initial commit, LedController and Led objects implemented, Led registration with LedController works correctly, and LedController thread works correctly (tested on Linux).
========= ========== ===================================================================================================