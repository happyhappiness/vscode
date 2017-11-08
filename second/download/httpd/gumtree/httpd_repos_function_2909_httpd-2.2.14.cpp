static int dbd_pgsql_get_row(apr_pool_t *pool, apr_dbd_results_t *res,
                             apr_dbd_row_t **rowp, int rownum)
{
    apr_dbd_row_t *row = *rowp;
    int sequential = ((rownum >= 0) && res->random) ? 0 : 1;

    if (row == NULL) {
        row = apr_palloc(pool, sizeof(apr_dbd_row_t));
        *rowp = row;
        row->res = res;
        if ( sequential ) {
            row->n = 0;
        }
        else {
            if (rownum > 0) {
                row->n = --rownum;
            }
            else {
                return -1; /* invalid row */
            }
        }
    }
    else {
        if ( sequential ) {
            ++row->n;
        }
        else {
            if (rownum > 0) {
                row->n = --rownum;
            }
            else {
                return -1; /* invalid row */
            }
        }
    }

    if (res->random) {
        if ((row->n >= 0) && (size_t)row->n >= res->ntuples) {
            *rowp = NULL;
            apr_pool_cleanup_run(pool, res->res, clear_result);
            res->res = NULL;
            return -1;
        }
    }
    else {
        if ((row->n >= 0) && (size_t)row->n >= res->ntuples) {
            /* no data; we have to fetch some */
            row->n -= res->ntuples;
            if (res->res != NULL) {
                PQclear(res->res);
            }
            res->res = PQgetResult(res->handle);
            if (res->res) {
                res->ntuples = PQntuples(res->res);
                while (res->ntuples == 0) {
                    /* if we got an empty result, clear it, wait a mo, try
                     * again */
                    PQclear(res->res);
                    apr_sleep(100000);        /* 0.1 secs */
                    res->res = PQgetResult(res->handle);
                    if (res->res) {
                        res->ntuples = PQntuples(res->res);
                    }
                    else {
                        return -1;
                    }
                }
                if (res->sz == 0) {
                    res->sz = PQnfields(res->res);
                }
            }
            else {
                return -1;
            }
        }
    }
    return 0;
}