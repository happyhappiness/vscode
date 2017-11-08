static const char *dbd_pgsql_get_name(const apr_dbd_results_t *res, int n)
{
    return (res->res ? PQfname(res->res, n) : NULL);
}