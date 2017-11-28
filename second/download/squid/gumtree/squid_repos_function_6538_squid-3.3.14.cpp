Mgr::OfflineToggleAction::Pointer
Mgr::OfflineToggleAction::Create(const Command::Pointer &cmd)
{
    return new OfflineToggleAction(cmd);
}