#pragma once

/*
 * Port ID Conventions
 * 
 * Ports 0-3: PCMs
 * Ports 0-9: All Solenoids
 * Ports 10-14: Drivetrain Talons
 * Ports 15-30: Other Talons
 * Ports 31-50: Any additional ports
 * 
*/

/* Drive ports */
#define RIGHT_FRONT_PORT 4
#define RIGHT_BACK_PORT 5
#define LEFT_FRONT_PORT 6
#define LEFT_BACK_PORT 7

/* Solenoids */
#define LEFT_DRIVE_SHIFTER_PCM 1
#define RIGHT_DRIVE_SHIFTER_PCM 1
#define WINCH_PCM 1
#define COMPRESSOR_PCM 0

#define LEFT_DRIVE_SHIFTER_LOW_GEAR_PORT 0
#define RIGHT_DRIVE_SHIFTER_LOW_GEAR_PORT 0
#define LEFT_DRIVE_SHIFTER_HIGH_GEAR_PORT 1
#define RIGHT_DRIVE_SHIFTER_HIGH_GEAR_PORT 1 

#define WINCH_RELEASE_PISTON_OUT_PORT 2
#define WINCH_RELEASE_PISTON_IN_PORT 3

#define UNNAMED_WINCH_RELEASE_PISTON_OUT_PORT 4
#define UNNAMED_WINCH_RELEASE_PISTON_IN_PORT 5

/* Launcher Ports */
#define WINCH_ONE_PORT 21
#define WINCH_TWO_PORT 22
