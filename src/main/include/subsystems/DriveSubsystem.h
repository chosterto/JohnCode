// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "ctre/Phoenix.h"
#include <frc/ADXRS450_Gyro.h>
#include "frc/SPI.h"
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"

using namespace nt;

class DriveSubsystem : public frc2::SubsystemBase {
 public:
  DriveSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void Drive(double x, double y);
  void DriveStop();
  double LeftEncoders();
  double RightEncoders();
  void ZeroDriveEncoders();
  double GetGyroAngle();

 private:
  NetworkTableInstance inst = NetworkTableInstance::GetDefault();
  std::shared_ptr<NetworkTable> datatable = inst.GetTable("datatable");

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonFX m_frontLeft{0};
  WPI_TalonFX m_backLeft{1};
  frc::MotorControllerGroup m_LeftGroup{m_frontLeft, m_backLeft};
  WPI_TalonFX m_frontRight{2};
  WPI_TalonFX m_backRight{3};
  frc::MotorControllerGroup m_RightGroup{ m_frontRight, m_backRight};
  frc::DifferentialDrive m_robotDrive{m_LeftGroup, m_RightGroup};
  
  frc::ADXRS450_Gyro m_gyro{frc::SPI::Port::kOnboardCS0};

};
