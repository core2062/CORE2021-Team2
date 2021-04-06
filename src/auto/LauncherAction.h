#pragma once

#include <CORERobotLib.h>
#include "LauncherSubsystem.h"

using namespace CORE;

enum launchAction {
    LAUNCHER_COCK,
    LAUNCHER_LAUNCH
};

class LauncherAction : public COREAutonAction {
public:
    LauncherAction(launchAction requestedLaunchAction);
    void ActionInit() override;
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd() override;

private:
    launchAction m_launchAction;
    LauncherWantedState m_wantedState;
    bool m_launcherDown;

};