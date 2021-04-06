#include "LauncherAction.h"
#include "Robot.h"

LauncherAction::LauncherAction(launchAction requestedLaunchAction) {
    m_launchAction = requestedLaunchAction;

}

void LauncherAction::ActionInit() {
    m_wantedState = Robot::GetInstance()->launcherSubsystem.wantedState;
    m_launcherDown = Robot::GetInstance()->launcherSubsystem.isLauncherDown;
    Robot::GetInstance()->teleopInit();
}

CORE::COREAutonAction::actionStatus LauncherAction::Action() {
    m_wantedState = Robot::GetInstance()->launcherSubsystem.wantedState;
    m_launcherDown = Robot::GetInstance()->launcherSubsystem.isLauncherDown;
    switch (m_launchAction)
    {
        case LAUNCHER_COCK:
            Robot::GetInstance()->launcherSubsystem.cockLauncher();
            m_wantedState = Robot::GetInstance()->launcherSubsystem.wantedState;
            m_launcherDown = Robot::GetInstance()->launcherSubsystem.isLauncherDown;
            if (m_wantedState == STANDBY && m_launcherDown == true)
            {
                return COREAutonAction::actionStatus::END;
            } else {
                return COREAutonAction::actionStatus::CONTINUE;
            }
            
            break;
        case LAUNCHER_LAUNCH:
            Robot::GetInstance()->launcherSubsystem.launch();
            break;

    }
    return COREAutonAction::actionStatus::END;
}

void LauncherAction::ActionEnd() {

}