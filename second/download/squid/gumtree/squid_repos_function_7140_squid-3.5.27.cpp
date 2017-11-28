void
Mgr::CountersAction::add(const Action& action)
{
    debugs(16, 5, HERE);
    data += dynamic_cast<const CountersAction&>(action).data;
}