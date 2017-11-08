static const char *dbd_mysql_get_name(const apr_dbd_results_t *res, int n)
{
    if ((n < 0) || (n >= (int) mysql_num_fields(res->res))) {
        return NULL;
    }

    return mysql_fetch_fields(res->res)[n].name;
}