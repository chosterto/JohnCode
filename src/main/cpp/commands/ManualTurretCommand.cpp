// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ManualTurretCommand.h"

ManualTurretCommand::ManualTurretCommand(TurretSubsystem* turretSubsystem, double speed) : m_turretSubsystem(turretSubsystem), m_speed(speed) {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void ManualTurretCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ManualTurretCommand::Execute() {
  m_turretSubsystem->MoveTurret(m_speed);
}

// Called once the command ends or is interrupted.
void ManualTurretCommand::End(bool interrupted) {
  m_turretSubsystem->MoveTurret(0.0);
}

// Returns true when the command should end.
bool ManualTurretCommand::IsFinished() {
  return false;
}
