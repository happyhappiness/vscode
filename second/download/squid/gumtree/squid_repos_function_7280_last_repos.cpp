void
Mgr::ServiceTimesAction::add(const Action& action)
{
    debugs(16, 5, HERE);
    data += dynamic_cast<const ServiceTimesAction&>(action).data;
}