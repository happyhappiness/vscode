Mgr::InfoAction::Pointer
Mgr::InfoAction::Create(const CommandPointer &cmd)
{
    return new InfoAction(cmd);
}