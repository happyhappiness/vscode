static int dbd_oracle_num_cols(apr_dbd_results_t* res)
{
    return res->statement->nout;
}