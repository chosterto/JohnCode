// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/DriveSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>

DriveSubsystem::DriveSubsystem() {
    m_frontLeft.SetInverted(false);
    m_backLeft.SetInverted(false);
    m_frontRight.SetInverted(true);
    m_backRight.SetInverted(true);
    
    ZeroDriveEncoders();
}

// This method will be called once per scheduler run
void DriveSubsystem::Periodic() {
    frc::SmartDashboard::PutNumber("Gyro Angle", GetGyroAngle());

    // Write to networktables
    datatable->PutNumber("encoders_left", LeftEncoders());
    datatable->PutNumber("encoders_right", RightEncoders());
    datatable->PutNumber("gyro", GetGyroAngle());
}

void DriveSubsystem::Drive(double x, double y) {
    m_robotDrive.ArcadeDrive(y, x);
}

void DriveSubsystem::DriveStop() {
    m_robotDrive.ArcadeDrive(0.0, 0.0);
}

double DriveSubsystem::LeftEncoders() {
    return (m_frontLeft.GetSelectedSensorPosition() + m_backLeft.GetSelectedSensorPosition()) / 2;
}

double DriveSubsystem::RightEncoders() {
    return (m_frontRight.GetSelectedSensorPosition() + m_backRight.GetSelectedSensorPosition()) / 2;
}

void DriveSubsystem::ZeroDriveEncoders() {
    m_frontLeft.SetSelectedSensorPosition(0.0);
    m_frontRight.SetSelectedSensorPosition(0.0);
    m_backLeft.SetSelectedSensorPosition(0.0);
    m_backRight.SetSelectedSensorPosition(0.0);
}

double DriveSubsystem::GetGyroAngle() {
    return m_gyro.GetAngle();
}
