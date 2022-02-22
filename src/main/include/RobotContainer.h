// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>

#include "Constants.h"
#include "frc/Joystick.h"
#include "frc/XboxController.h"

#include "commands/ExampleCommand.h"
#include "subsystems/ExampleSubsystem.h"
#include "subsystems/DriveSubsystem.h"
#include "subsystems/TurretSubsystem.h"
#include "subsystems/ShooterSubsystem.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();

 private:
  frc::Joystick m_joy{OIConstants::kDriverController};
  frc::XboxController m_driverController{OIConstants::kDriverController};
  
  // The robot's subsystems and commands are defined here...
  ExampleSubsystem m_subsystem;
  ExampleCommand m_autonomousCommand;
  DriveSubsystem m_driveSubsystem;
  TurretSubsystem m_turretSubsystem;
  ShooterSubsystem m_shootersubsystem;

  void ConfigureButtonBindings();
};
