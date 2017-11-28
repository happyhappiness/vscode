SBufStatsAction::Pointer
SBufStatsAction::Create(const Mgr::CommandPointer &cmd)
{
    return new SBufStatsAction(cmd);
}