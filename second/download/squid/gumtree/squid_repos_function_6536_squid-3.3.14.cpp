Mgr::RotateAction::Pointer
Mgr::RotateAction::Create(const Command::Pointer &cmd)
{
    return new RotateAction(cmd);
}