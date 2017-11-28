ACL *
ACL::FindByName(const char *name)
{
    ACL *a;
    debugs(28, 9, "ACL::FindByName '" << name << "'");

    for (a = Config.aclList; a; a = a->next)
        if (!strcasecmp(a->name, name))
            return a;

    debugs(28, 9, "ACL::FindByName found no match");

    return NULL;
}