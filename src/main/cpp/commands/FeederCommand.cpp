// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/FeederCommand.h"

FeederCommand::FeederCommand(ShooterSubsystem* shootersubsystem, double speed) : m_shootersubsystem(shootersubsystem), m_speed(speed) {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void FeederCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void FeederCommand::Execute() {
  m_shootersubsystem->FeederMove(m_speed);
}

// Called once the command ends or is interrupted.
void FeederCommand::End(bool interrupted) {
  m_shootersubsystem->FeederStop();
}

// Returns true when the command should end.
bool FeederCommand::IsFinished() {
  return false;
}
