// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Constants.h"
#include "subsystems/ShooterSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>

#define DEGREES_TO_RADIANS (M_PI / 180)


ShooterSubsystem::ShooterSubsystem() {
    flywheelMotorL.SetInverted(false);
    flywheelMotorR.SetInverted(true);

    feederMotor.SetInverted(true);
    feederMotorBottom.SetInverted(true);
}

// This method will be called once per scheduler run
void ShooterSubsystem::Periodic() {
    frc::SmartDashboard::PutNumber("Flywheel Velocity", velocity);

    targetFound = limetable->GetNumber("tv", 0.0);

    if (targetFound) {
        verticalError = limetable->GetNumber("ty", 0.0);
        xDistance = (hubHeight - cameraHeight) / tan((verticalError + mountingAngle) * DEGREES_TO_RADIANS);
        velocity = (xDistance / time) / cos(shootingAngle * DEGREES_TO_RADIANS);
    }

    ShooterMove(velocity / (10 * ShooterConstants::kFlywheelTicksToInches));
}

void ShooterSubsystem::ShooterMove(double velocity) {
    // in raw sensor units per 100 ms
    flywheelMotorL.Set(ControlMode::Velocity, velocity);
    flywheelMotorR.Set(ControlMode::Velocity, velocity);
}

void ShooterSubsystem::ShooterStop() {
    flywheelMotorL.Set(ControlMode::Velocity, 0.0);
    flywheelMotorR.Set(ControlMode::Velocity, 0.0);
}

void ShooterSubsystem::FeederMove(double speed) {
    feederMotor.Set(ControlMode::PercentOutput, speed);
    feederMotorBottom.Set(ControlMode::PercentOutput, speed);
}

void ShooterSubsystem::FeederStop() {
    feederMotor.Set(ControlMode::PercentOutput, 0.0);
    feederMotorBottom.Set(ControlMode::PercentOutput, 0.0);
}
