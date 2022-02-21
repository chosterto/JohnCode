// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/JoystickButton.h>

#include "commands/DriveCommand.h"
#include "commands/ManualTurretCommand.h"

RobotContainer::RobotContainer() : m_autonomousCommand(&m_subsystem) {
  // Initialize all of your commands and subsystems here
  m_driveSubsystem.SetDefaultCommand(
    DriveCommand(
      &m_driveSubsystem,
      [this]() { return m_joy.GetRawAxis(0); },
      [this]() { return -m_joy.GetRawAxis(1); }
    )
  );

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  frc2::Button J0B1{[&] { return m_driverController.GetRawButton(1); }};
  frc2::Button J0B2{[&] { return m_driverController.GetRawButton(2); }};

  J0B1.WhileHeld(ManualTurretCommand(&m_turretSubsystem, 1.0));
  J0B2.WhileHeld(ManualTurretCommand(&m_turretSubsystem, -1.0));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}
