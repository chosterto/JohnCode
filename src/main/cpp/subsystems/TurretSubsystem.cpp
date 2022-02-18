// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Constants.h"
#include "subsystems/TurretSubsystem.h"
#include "subsystems/DriveSubsystem.h"
#include <iostream>
#include <cmath>

#define DEGREES_TO_RADIANS (M_PI / 180)
#define RADIANS_TO_DEGREES (180 / M_PI)
#define INCHES_TO_FEET 0.083333333


TurretSubsystem::TurretSubsystem() : m_gain(0.1) {
    ZeroTurretEncoder();
}

// This method will be called once per scheduler run
void TurretSubsystem::Periodic() {
    frc::SmartDashboard::PutNumber("Turret Encoder", GetTurretPos());
    frc::SmartDashboard::PutNumber("Turret Angle", turretAngle);
    frc::SmartDashboard::PutNumber("Hub Angle", hubAngle);
    frc::SmartDashboard::PutNumber("Error", m_error);
    
    // Encoder and gyro values from drive subsystem
    currentLeft = datatable->GetNumber("encoders_left", 0.0);
    currentRight = datatable->GetNumber("encoders_right", 0.0);
    robotAngle = datatable->GetNumber("gyro", 0.0);

    currentLeft *= DriveConstants::kDriveTicksToInches * INCHES_TO_FEET;
    currentRight *= DriveConstants::kDriveTicksToInches * INCHES_TO_FEET;
    frc::Rotation2d gyroAngle{units::degree_t(robotAngle)};
    m_odometry.Update(gyroAngle, units::foot_t(currentLeft), units::foot_t(currentRight));

    // Get x and y values of robot relative to hub
    yRobotFeet = units::foot_t(m_odometry.GetPose().X());
    // Invert X direction 
    xCurrent = units::foot_t(m_odometry.GetPose().Y());
    xRobotFeet -= (xCurrent - xPrev);
    xPrev = xCurrent;
    
    // Calculate the angle needed to turn towards the hub
    hubAngle = atan2(yRobotFeet.to<double>(), xRobotFeet.to<double>()) * RADIANS_TO_DEGREES;
    turretAngle = fmod(robotAngle + EstimateTurretAngle(GetTurretPos()), 360.0);
    m_error = FindTurretError(hubAngle, turretAngle);

    // Loop around if error exceeds range of turret
    if (m_error > 360.0 - turretFOV) m_error -= 360;
    if (m_error < turretFOV - 360.0) m_error += 360;

    // Calculate speed based on error
    m_speed = Clamp(m_error * m_gain, 1.0);

    // Limit turret rotation
    if ( (GetTurretPos() > 6000 && m_speed > 0) || (GetTurretPos() < -6000 && m_speed < 0) ) {
        m_speed = 0.0;
    }

    turretMotor.Set(ControlMode::PercentOutput, m_speed);
    
}

void TurretSubsystem::MoveTurret(double speed) {
    turretMotor.Set(ControlMode::PercentOutput, speed);
}

double TurretSubsystem::GetTurretPos() {
    return turretMotor.GetSelectedSensorPosition();
}

void TurretSubsystem::ZeroTurretEncoder() {
    turretMotor.SetSelectedSensorPosition(0.0);
}

double TurretSubsystem::EstimateTurretAngle(double ticks) { 
    // theta = arc length / radius
    return (ticks * TurretConstants::kTurretTicksToInches) / TurretConstants::kTurretRadiusInches * RADIANS_TO_DEGREES; 
}

double TurretSubsystem::FindTurretError(double centerAngle, double turretAngle) {
    if (centerAngle >= 0 && centerAngle < 90) {
        return (90 - turretAngle) + centerAngle;
    } 
    
    if (centerAngle > 90) {
        return -(turretAngle + 90 + (180 - centerAngle));
    }

    if (centerAngle < 0 && centerAngle > -90) {
        return (90 - turretAngle) - std::abs(centerAngle);
    }

    return -(turretAngle + std::abs(centerAngle) - 90);
}

double TurretSubsystem::Clamp(double value, double max) {
    if (std::abs(value) > max) {
        value = (value > 0) ? max : -max;
    }

    return value;
}
