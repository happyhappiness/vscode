char *case_filename(apr_pool_t *pPool, const char *szFile)
{
    char *casedFileName = NULL;
    char name[1024];
    int rc;

#ifdef NEW_API
    rc = realname(szFile, name);
    if (rc == 0) {
        casedFileName = apr_pstrdup(pPool, name);
    }
#else
    NXDirAttrWithName_t	*attrBuf;

    attrBuf = (NXDirAttrWithName_t *) &name;
    rc =NXGetAttr(NULL, szFile, NX_DELEVEL_NAME_ONLY, attrBuf, 1024, 0);
    if (rc == 0) {
        casedFileName = apr_pstrdup(pPool, attrBuf->deName);
    }
#endif
    else
    {
        char *s;
        s = strrchr(szFile, '/');
        if (!s)
            s = strrchr(szFile, ':');
        if (s) {
            casedFileName = apr_pstrdup(pPool, &s[1]);
        }
    }
    return casedFileName;
}