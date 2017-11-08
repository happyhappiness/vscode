static apr_status_t dav_fs_mktemp(apr_file_t **fp, char *templ, apr_pool_t *p)
{
    apr_status_t rv;
    int num = ((getpid() << 7) + (apr_uintptr_t)templ % (1 << 16) ) %
               ( 1 << 23 ) ;
    char *numstr = templ + strlen(templ) - 6;

    ap_assert(numstr >= templ);

    do {
        num = (num + 1) % ( 1 << 23 );
        apr_snprintf(numstr, 7, "%06x", num);
        rv = apr_file_open(fp, templ,
                           APR_WRITE | APR_CREATE | APR_BINARY | APR_EXCL,
                           APR_OS_DEFAULT, p);
    } while (APR_STATUS_IS_EEXIST(rv));

    return rv;
}