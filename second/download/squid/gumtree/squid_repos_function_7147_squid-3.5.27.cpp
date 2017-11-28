void
Mgr::InfoAction::add(const Action& action)
{
    debugs(16, 5, HERE);
    data += dynamic_cast<const InfoAction&>(action).data;
}