const char *
CacheManager::ActionProtection(const CacheManagerAction * at)
{
    char *pwd;
    assert(at);
    pwd = PasswdGet(Config.passwd_list, at->action);

    if (!pwd)
        return at->flags.pw_req ? "hidden" : "public";

    if (!strcmp(pwd, "disable"))
        return "disabled";

    if (strcmp(pwd, "none") == 0)
        return "public";

    return "protected";
}