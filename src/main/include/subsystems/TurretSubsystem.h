// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "ctre/Phoenix.h"
#include "frc/smartdashboard/Smartdashboard.h"
#include "frc/kinematics/DifferentialDriveOdometry.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableValue.h"
#include "wpi/span.h"

using namespace nt;

class TurretSubsystem : public frc2::SubsystemBase {
 public:
  TurretSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void MoveTurret(double speed);
  double GetTurretPos();
  double EstimateTurretAngle(double ticks);
  void ZeroTurretEncoder();
  double FindTurretError(double centerAngle, double turretAngle);
  double Clamp(double value, double max);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  NetworkTableInstance inst = NetworkTableInstance::GetDefault();
  std::shared_ptr<NetworkTable> limetable = inst.GetTable("limelight");
  std::shared_ptr<NetworkTable> datatable = inst.GetTable("datatable");

  TalonSRX turretMotor{6};

  double m_gain;
  double m_error = 0.0;
  double m_speed = 0.0;
  bool m_targetFound;

  // Starting configuration
  units::foot_t xRobotFeet = 0.0_ft;
  units::foot_t yRobotFeet = -4.17_ft;
  double offsetAngle = 0.0;

  units::foot_t xPrev = xRobotFeet;
  units::foot_t xCurrent;
  double turretFOV = 180.0;
  double turretAngle = 0.0;
  double hubAngle = 0.0;
  double currentLeft;
  double currentRight;
  double previousLeft = 0.0;
  double previousRight = 0.0;
  double deltaLeft;
  double deltaRight;
  double robotAngle;


  frc::DifferentialDriveOdometry m_odometry{frc::Rotation2d(0_deg), frc::Pose2d{yRobotFeet, xRobotFeet, 0_deg}};

};
