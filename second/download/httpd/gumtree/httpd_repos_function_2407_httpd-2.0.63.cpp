static void vt_sdbm_usednames(apr_pool_t *pool, const char *pathname,
                              const char **used1, const char **used2)
{
    char *work;

    /* ### this could be optimized by computing strlen() once and using
       ### memcpy and pmemdup instead. but why bother? */

    *used1 = apr_pstrcat(pool, pathname, APR_SDBM_DIRFEXT, NULL);
    *used2 = work = apr_pstrdup(pool, *used1);

    /* we know the extension is 4 characters */
    memcpy(&work[strlen(work) - 4], APR_SDBM_PAGFEXT, 4);
}