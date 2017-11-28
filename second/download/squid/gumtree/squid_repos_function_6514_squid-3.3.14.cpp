const Mgr::Action&
Mgr::Response::getAction() const
{
    Must(hasAction());
    return *action;
}