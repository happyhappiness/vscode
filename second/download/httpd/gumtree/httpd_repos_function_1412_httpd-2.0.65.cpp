static void build_cert_list (apr_pool_t *p)
{
    int i;
    char **rootcerts = (char **)certlist->elts;

    numcerts = certlist->nelts;
    certarray = apr_palloc(p, sizeof(unicode_t*)*numcerts);

    for (i = 0; i < numcerts; ++i) {
        unicode_t *unistr;
        unistr = (unicode_t*)apr_palloc(p, strlen(rootcerts[i])*4);
        loc2uni (UNI_LOCAL_DEFAULT, unistr, rootcerts[i], 0, 2);
        certarray[i] = unistr;
    }
}