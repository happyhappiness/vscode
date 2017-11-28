Mgr::Action::Pointer
CacheManager::createNamedAction(const char *actionName)
{
    Must(actionName);

    Mgr::Command::Pointer cmd = new Mgr::Command;
    cmd->profile = findAction(actionName);
    cmd->params.actionName = actionName;

    Must(cmd->profile != NULL);
    return cmd->profile->creator->create(cmd);
}