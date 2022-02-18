// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace TurretConstants {
    constexpr double kEncoderTicksPerTurretRev = 24000;
    constexpr double kTurretCircumference = 43.98;
    constexpr double kTurretRadiusInches = 7.0; // 19 inch turning radius

    constexpr double kTurretTicksToInches = kTurretCircumference / kEncoderTicksPerTurretRev;  
}

namespace DriveConstants {
    constexpr double kDriveEncoderTicksPerRev = 2048;
    constexpr double kDriveGearRatio = 10;
    constexpr double kWheelCircumference = 19.63;

    constexpr double kDriveTicksToInches = kWheelCircumference / (kDriveEncoderTicksPerRev * kDriveGearRatio);
}

namespace OIConstants {
    constexpr int kDriverController = 0;
}