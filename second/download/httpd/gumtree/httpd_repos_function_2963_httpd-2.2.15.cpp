static int dbd_pgsql_num_tuples(apr_dbd_results_t* res)
{
    if (res->random) {
        return res->ntuples;
    }
    else {
        return -1;
    }
}