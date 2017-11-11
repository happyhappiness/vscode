static int exists(char *fname, apr_pool_t *pool)
{
    apr_finfo_t sbuf;
    apr_status_t check;

    check = apr_stat(&sbuf, fname, APR_FINFO_TYPE, pool);
    return ((check || sbuf.filetype != APR_REG) ? 0 : 1);
}