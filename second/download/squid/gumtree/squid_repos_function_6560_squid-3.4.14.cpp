Mgr::CountersAction::Pointer
Mgr::CountersAction::Create(const CommandPointer &cmd)
{
    return new CountersAction(cmd);
}