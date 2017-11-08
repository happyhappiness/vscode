static void vt_gdbm_usednames(apr_pool_t *pool, const char *pathname,
                              const char **used1, const char **used2)
{
    *used1 = apr_pstrdup(pool, pathname);
    *used2 = NULL;
}