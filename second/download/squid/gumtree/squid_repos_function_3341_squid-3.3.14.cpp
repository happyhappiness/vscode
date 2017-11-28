int
snmpCreateOidFromStr(const char *str, oid **name, int *nl)
{
    char const *delim = ".";
    char *p;

    *name = NULL;
    *nl = 0;
    char *s = xstrdup(str);
    char *s_ = s;

    /* Parse the OID string into oid bits */
    while ( (p = strsep(&s_, delim)) != NULL) {
        *name = (oid*)xrealloc(*name, sizeof(oid) * ((*nl) + 1));
        (*name)[*nl] = atoi(p);
        ++(*nl);
    }

    xfree(s);
    return 1;
}