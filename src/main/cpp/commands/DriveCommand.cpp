// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/DriveCommand.h"

DriveCommand::DriveCommand(
  DriveSubsystem* driveSubsystem, 
  std::function<double()> xx, 
  std::function<double()> yy) : m_driveSubsystem(driveSubsystem), m_xx(xx), m_yy(yy) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({m_driveSubsystem});
}

// Called when the command is initially scheduled.
void DriveCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveCommand::Execute() {
  m_driveSubsystem->Drive(m_xx(), m_yy());
}

// Called once the command ends or is interrupted.
void DriveCommand::End(bool interrupted) {
  m_driveSubsystem->DriveStop();
}

// Returns true when the command should end.
bool DriveCommand::IsFinished() {
  return false;
}
