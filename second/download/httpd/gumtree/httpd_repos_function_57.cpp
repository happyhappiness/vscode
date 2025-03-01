static void delete_file(char *path, char *basename, apr_pool_t *pool)
{
    char *nextpath;
    apr_pool_t *p;

    if (dryrun) {
        return;
    }

    /* temp pool, otherwise lots of memory could be allocated */
    apr_pool_create(&p, pool);
    nextpath = apr_pstrcat(p, path, "/", basename, NULL);
    apr_file_remove(nextpath, p);
    apr_pool_destroy(p);

    if (benice) {
        if (++delcount >= DELETE_NICE) {
            apr_sleep(NICE_DELAY);
            delcount = 0;
        }
    }
}