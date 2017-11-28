void
SBufStatsAction::add(const Mgr::Action& action)
{
    sbdata += dynamic_cast<const SBufStatsAction&>(action).sbdata;
    mbdata += dynamic_cast<const SBufStatsAction&>(action).mbdata;
    sbsizesatdestruct += dynamic_cast<const SBufStatsAction&>(action).sbsizesatdestruct;
    mbsizesatdestruct += dynamic_cast<const SBufStatsAction&>(action).mbsizesatdestruct;
}