#pragma once

/*
 * Port ID Conventions
 * 
 * Ports 0-3: PCMs
 * Ports 4-7: Drivetrain Talons
 * Ports 8-9: Drivetrain Shifters
 * Ports 10-20: Other Solenoids
 * Ports 21-30: Other Talons
 * Ports 31-50: Any additional ports
 * 
*/

/* Drive ports */
#define RIGHT_FRONT_PORT 4
#define RIGHT_BACK_PORT 5
#define LEFT_FRONT_PORT 6
#define LEFT_BACK_PORT 7

/* Solenoids */
#define LEFT_DRIVE_SHIFTER_PCM 0
#define RIGHT_DRIVE_SHIFTER_PCM 0
#define COMPRESSOR_PCM 0
#define WINCH_PCM 0

#define LEFT_DRIVE_SHIFTER_LOW_GEAR_PORT 8
#define RIGHT_DRIVE_SHIFTER_LOW_GEAR_PORT 8
#define LEFT_DRIVE_SHIFTER_HIGH_GEAR_PORT 9
#define RIGHT_DRIVE_SHIFTER_HIGH_GEAR_PORT 9 

#define WINCH_PISTON_OUT_PORT 10
#define WINCH_PISTON_IN_PORT 11

/* Launcher Ports */
#define WINCH_PORT 21
