static const char *dbd_pgsql_get_name(const apr_dbd_results_t *res, int n)
{
    if (res->res) {
        if ((n>=0) && (PQnfields(res->res) > n)) {
            return PQfname(res->res,n);
        }
    }
    return NULL;
}