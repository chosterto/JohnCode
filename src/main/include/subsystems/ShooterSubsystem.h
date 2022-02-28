// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "ctre/Phoenix.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"

using namespace nt;

class ShooterSubsystem : public frc2::SubsystemBase {
 public:
  ShooterSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void ShooterMove(double velocity);
  void ShooterStop();
  void FeederMove(double speed);
  void FeederStop();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  NetworkTableInstance inst = NetworkTableInstance::GetDefault();
  std::shared_ptr<NetworkTable> limetable = inst.GetTable("limelight");

  WPI_TalonFX flywheelMotorL{14};
  WPI_TalonFX flywheelMotorR{15};
  WPI_TalonFX feederMotorBottom{12};
  WPI_TalonSRX feederMotor{8};

  double shootingAngle = 60.0;
  double time = 1.5;
  double hubHeight = 104.00004;
  double cameraHeight = 27.0;
  double mountingAngle = 40.0;
  double verticalError;
  double distance = 0.0;
  bool targetFound;
};
