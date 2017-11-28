Mgr::ReconfigureAction::Pointer
Mgr::ReconfigureAction::Create(const Command::Pointer &cmd)
{
    return new ReconfigureAction(cmd);
}