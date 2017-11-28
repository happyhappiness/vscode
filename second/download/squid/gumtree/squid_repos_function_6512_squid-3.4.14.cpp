Mgr::StoreIoAction::Pointer
Mgr::StoreIoAction::Create(const CommandPointer &cmd)
{
    return new StoreIoAction(cmd);
}