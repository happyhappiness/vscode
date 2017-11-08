static int dbd_sqlite_get_row(apr_pool_t * pool, apr_dbd_results_t * res,
                              apr_dbd_row_t ** rowp, int rownum)
{
    apr_dbd_row_t *row = *rowp;
    int sequential = ((rownum >= 0) && res->random) ? 0 : 1;

    if (row == NULL) {
        row = apr_palloc(pool, sizeof(apr_dbd_row_t));
        *rowp = row;
        row->res = res;
        row->n = sequential ? 0 : rownum - 1;
    }
    else {
        if (sequential) {
            ++row->n;
        }
        else {
            row->n = rownum - 1;
        }
    }

    if (row->n >= res->ntuples) {
        *rowp = NULL;
        apr_pool_cleanup_run(pool, res->res, free_table);
        res->res = NULL;
        return -1;
    }

    /* Pointer magic explanation:
     *      The sqlite result is an array such that the first res->sz elements are 
     *      the column names and each tuple follows afterwards 
     *      ex: (from the sqlite2 documentation)
     SELECT employee_name, login, host FROM users WHERE login LIKE *        'd%';

     nrow = 2
     ncolumn = 3
     result[0] = "employee_name"
     result[1] = "login"
     result[2] = "host"
     result[3] = "dummy"
     result[4] = "No such user"
     result[5] = 0
     result[6] = "D. Richard Hipp"
     result[7] = "drh"
     result[8] = "zadok"
     */

    row->data = res->res + res->sz + (res->sz * row->n);

    return 0;
}