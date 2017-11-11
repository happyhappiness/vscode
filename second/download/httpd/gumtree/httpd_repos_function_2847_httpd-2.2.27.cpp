static int dbd_sqlite3_get_row(apr_pool_t *pool, apr_dbd_results_t *res,
                               apr_dbd_row_t **rowp, int rownum)
{
    int i = 0;

    if (rownum == -1) {
        *rowp = res->next_row;
        if (*rowp == 0)
            return -1;
        res->next_row = (*rowp)->next_row;
        return 0;
    }
    if (rownum > res->tuples) {
        return -1;
    }
    rownum--;
    *rowp = res->next_row;
    for (; *rowp != 0; i++, *rowp = (*rowp)->next_row) {
        if (i == rownum) {
            return 0;
        }
    }

    return -1;

}