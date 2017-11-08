static int dbd_freetds_get_row(apr_pool_t *pool, apr_dbd_results_t *res,
                               apr_dbd_row_t **rowp, int rownum)
{
    RETCODE rv = 0;
    apr_dbd_row_t *row = *rowp;
    int sequential = ((rownum >= 0) && res->random) ? 0 : 1;

    if (row == NULL) {
        row = apr_palloc(pool, sizeof(apr_dbd_row_t));
        *rowp = row;
        row->res = res;
    }
    /*
    else {
        if ( sequential ) {
            ++row->n;
        }
        else {
            row->n = rownum;
        }
    }
    */
    if (sequential) {
        rv = dbnextrow(res->proc);
    }
    else {
        rv = (rownum >= 0) ? dbgetrow(res->proc, rownum) : NO_MORE_ROWS;
    }
    switch (rv) {
    case SUCCEED: return 0;
    case REG_ROW: return 0;
    case NO_MORE_ROWS:
        apr_pool_cleanup_run(pool, res->proc, clear_result);
        *rowp = NULL;
        return -1;
    case FAIL: return 1;
    case BUF_FULL: return 2; /* FIXME */
    default: return 3;
    }

    return 0;
}