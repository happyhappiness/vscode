static void fake_file_remove(char *pathname, apr_pool_t *p)
{
    apr_finfo_t info;

    /* stat and printing to simulate some deletion system load and to
       display what would actually have happened */
    apr_stat(&info, pathname, DIRINFO, p);
    apr_file_printf(errfile, "would delete %s" APR_EOL_STR, pathname);
}