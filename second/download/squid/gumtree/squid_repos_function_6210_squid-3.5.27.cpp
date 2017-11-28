void
DiskdAction::add(const Action& action)
{
    debugs(79, 5, HERE);
    data += dynamic_cast<const DiskdAction&>(action).data;
}