DiskdAction::Pointer
DiskdAction::Create(const Mgr::CommandPointer &aCmd)
{
    return new DiskdAction(aCmd);
}