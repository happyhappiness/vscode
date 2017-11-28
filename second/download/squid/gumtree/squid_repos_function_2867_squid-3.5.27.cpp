const char *
CacheManager::ActionProtection(const Mgr::ActionProfile::Pointer &profile)
{
    assert(profile != NULL);
    const char *pwd = PasswdGet(Config.passwd_list, profile->name);

    if (!pwd)
        return profile->isPwReq ? "hidden" : "public";

    if (!strcmp(pwd, "disable"))
        return "disabled";

    if (strcmp(pwd, "none") == 0)
        return "public";

    return "protected";
}