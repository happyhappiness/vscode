Mgr::ShutdownAction::Pointer
Mgr::ShutdownAction::Create(const Command::Pointer &cmd)
{
    return new ShutdownAction(cmd);
}