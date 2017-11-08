static const char *dbd_freetds_get_name(const apr_dbd_results_t *res, int n)
{
    return (const char*) dbcolname(res->proc, n+1); /* numbering starts at 1 */
}