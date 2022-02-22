// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/ShooterSubsystem.h"

#define DEGREES_TO_RADIANS (M_PI / 180)


ShooterSubsystem::ShooterSubsystem() {
    flywheelMotorL.SetInverted(false);
    flywheelMotorR.SetInverted(true);
}

// This method will be called once per scheduler run
void ShooterSubsystem::Periodic() {
    targetFound = limetable->GetNumber("tv", 0.0);

    if (targetFound) {
        verticalError = limetable->GetNumber("ty", 0.0);
        xDistance = (hubHeight - cameraHeight) / tan((verticalError + mountingAngle) * DEGREES_TO_RADIANS);
        velocity = (xDistance / time) / cos(shootingAngle * DEGREES_TO_RADIANS);
    }

}

void ShooterSubsystem::ShooterMove(double velocity) {
    flywheelMotorL.Set(ControlMode::Velocity, velocity);
    flywheelMotorR.Set(ControlMode::Velocity, velocity);
}

void ShooterSubsystem::ShooterStop() {
    flywheelMotorL.Set(ControlMode::Velocity, 0.0);
    flywheelMotorR.Set(ControlMode::Velocity, 0.0);
}

