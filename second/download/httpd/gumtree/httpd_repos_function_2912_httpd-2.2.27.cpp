static apr_status_t dbd_oracle_check_conn(apr_pool_t *pool, apr_dbd_t *sql)
{
    apr_dbd_results_t *res = NULL;
    apr_dbd_row_t *row = NULL;
    
    if(dbd_oracle_pselect(pool, sql, &res, sql->check_conn_stmt,
                          0, NULL) != 0) {
        return APR_EGENERAL;
    }
    
    if(dbd_oracle_get_row(pool, res, &row, -1) != 0) {
        return APR_EGENERAL;
    }
    
    if(dbd_oracle_get_row(pool, res, &row, -1) != -1) {
        return APR_EGENERAL;
    }

    return APR_SUCCESS;
}