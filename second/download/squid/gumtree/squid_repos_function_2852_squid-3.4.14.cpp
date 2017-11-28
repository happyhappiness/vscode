Mgr::Action::Pointer
CacheManager::createRequestedAction(const Mgr::ActionParams &params)
{
    Mgr::Command::Pointer cmd = new Mgr::Command;
    cmd->params = params;
    cmd->profile = findAction(params.actionName.termedBuf());
    Must(cmd->profile != NULL);
    return cmd->profile->creator->create(cmd);
}