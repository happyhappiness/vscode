static const char *dbd_sqlite3_get_name(const apr_dbd_results_t *res, int n)
{
    if ((n < 0) || ((size_t)n >= res->sz)) {
        return NULL;
    }

    return res->col_names[n];
}