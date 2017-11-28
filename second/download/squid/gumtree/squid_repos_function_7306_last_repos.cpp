const Mgr::Command &
Mgr::Action::command() const
{
    Must(cmd != NULL);
    return *cmd;
}