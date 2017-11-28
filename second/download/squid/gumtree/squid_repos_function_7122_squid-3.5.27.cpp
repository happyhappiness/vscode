void
Mgr::IntervalAction::add(const Action& action)
{
    debugs(16, 5, HERE);
    data += dynamic_cast<const IntervalAction&>(action).data;
}