static const char *dbd_sqlite_get_name(const apr_dbd_results_t *res, int n)
{
    if ((n < 0) || (n >= res->sz)) {
        return NULL;
    }

    return res->res[n];
}