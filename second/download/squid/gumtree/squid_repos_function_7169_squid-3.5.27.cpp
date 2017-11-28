Mgr::IoAction::Pointer
Mgr::IoAction::Create(const CommandPointer &cmd)
{
    return new IoAction(cmd);
}