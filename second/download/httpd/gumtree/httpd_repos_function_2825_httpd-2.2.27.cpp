static int odbc_num_cols(apr_dbd_results_t *res)
{
    return res->ncols;
}