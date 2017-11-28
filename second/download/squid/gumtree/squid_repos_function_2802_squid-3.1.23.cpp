int
CacheManager::CheckPassword(cachemgrStateData * mgr)
{
    char *pwd = PasswdGet(Config.passwd_list, mgr->action);
    CacheManagerAction *a = findAction(mgr->action);

    debugs(16, 4, "CacheManager::CheckPassword for action " << mgr->action);
    assert(a != NULL);

    if (pwd == NULL)
        return a->flags.pw_req;

    if (strcmp(pwd, "disable") == 0)
        return 1;

    if (strcmp(pwd, "none") == 0)
        return 0;

    if (!mgr->passwd)
        return 1;

    return strcmp(pwd, mgr->passwd);
}