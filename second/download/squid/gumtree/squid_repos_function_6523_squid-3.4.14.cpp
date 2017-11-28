Mgr::ServiceTimesAction::Pointer
Mgr::ServiceTimesAction::Create(const CommandPointer &cmd)
{
    return new ServiceTimesAction(cmd);
}