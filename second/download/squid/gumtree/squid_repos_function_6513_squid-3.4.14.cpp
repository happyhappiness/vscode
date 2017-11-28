void
Mgr::StoreIoAction::add(const Action& action)
{
    debugs(16, 5, HERE);
    data += dynamic_cast<const StoreIoAction&>(action).data;
}