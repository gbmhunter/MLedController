========
MFlasher
========

---------------------------------------------------------------------------------------------
A microcontroller friendly C++ module to flash your LEDs (and other things).
---------------------------------------------------------------------------------------------

.. image:: https://api.travis-ci.org/mbedded-ninja/MFlasher.png?branch=master   
	:target: https://travis-ci.org/mbedded-ninja/MFlasher

- Author: gbmhunter <gbmhunter@gmail.com> (www.mbedded.ninja)
- First Ever Commit: 2014-10-13
- Last Modified: 2014-10-14
- Version: v1.0.0.0
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


Features:

- Dynamic allocation and resize capabilities (with data preservation)
- Embedded (microcontroller) support
- Small flash/RAM memory footprint (no depedance on the C++ std::string class)
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
v1.0.0.0  2014-10-14 Initial commit, LedController and Led objects implemented, Led registration with LedController works correctly, and LedController thread works correctly (tested on Linux).
========= ========== ===================================================================================================