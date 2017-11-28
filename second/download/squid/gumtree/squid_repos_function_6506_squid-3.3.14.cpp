void
Mgr::IoAction::add(const Action& action)
{
    debugs(16, 5, HERE);
    data += dynamic_cast<const IoAction&>(action).data;
}