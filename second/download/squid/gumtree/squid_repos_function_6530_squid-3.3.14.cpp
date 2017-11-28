Mgr::MenuAction::Pointer
Mgr::MenuAction::Create(const Command::Pointer &cmd)
{
    return new MenuAction(cmd);
}