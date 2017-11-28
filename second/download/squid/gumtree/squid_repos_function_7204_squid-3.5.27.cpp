void
Mgr::RegisterBasics()
{
    RegisterAction("index", "Cache Manager Interface", &Mgr::IndexAction::Create, 0, 1);
    RegisterAction("menu", "Cache Manager Menu", &Mgr::MenuAction::Create, 0, 1);
    RegisterAction("offline_toggle", "Toggle offline_mode setting", &Mgr::OfflineToggleAction::Create, 1, 1);
    RegisterAction("shutdown", "Shut Down the Squid Process", &Mgr::ShutdownAction::Create, 1, 1);
    RegisterAction("reconfigure", "Reconfigure Squid", &Mgr::ReconfigureAction::Create, 1, 1);
    RegisterAction("rotate", "Rotate Squid Logs", &Mgr::RotateAction::Create, 1, 1);
}