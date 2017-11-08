static int dbd_sqlite3_num_tuples(apr_dbd_results_t *res)
{
    return res->tuples;
}