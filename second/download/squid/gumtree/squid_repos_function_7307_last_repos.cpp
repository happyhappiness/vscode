bool
Mgr::Action::atomic() const
{
    return command().profile->isAtomic;
}