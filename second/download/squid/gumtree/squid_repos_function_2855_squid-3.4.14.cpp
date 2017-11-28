int
CacheManager::CheckPassword(const Mgr::Command &cmd)
{
    assert(cmd.profile != NULL);
    const char *action = cmd.profile->name;
    char *pwd = PasswdGet(Config.passwd_list, action);

    debugs(16, 4, "CacheManager::CheckPassword for action " << action);

    if (pwd == NULL)
        return cmd.profile->isPwReq;

    if (strcmp(pwd, "disable") == 0)
        return 1;

    if (strcmp(pwd, "none") == 0)
        return 0;

    if (!cmd.params.password.size())
        return 1;

    return cmd.params.password != pwd;
}