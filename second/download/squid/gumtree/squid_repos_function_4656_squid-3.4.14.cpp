void
ACL::context(const char *aName, const char *aCfgLine)
{
    name[0] = '\0';
    if (aName)
        xstrncpy(name, aName, ACL_NAME_SZ-1);
    safe_free(cfgline);
    if (aCfgLine)
        cfgline = xstrdup(aCfgLine);
}