static int dbd_mysql_get_row(apr_pool_t *pool, apr_dbd_results_t *res,
                             apr_dbd_row_t **row, int rownum)
{
    MYSQL_ROW r = NULL;
    int ret = 0;

    if (res->statement) {
        if (res->random) {
            if (rownum > 0) {
                mysql_stmt_data_seek(res->statement, (my_ulonglong) --rownum);
            }
            else {
                return -1; /* invalid row */
            }
        }
        ret = mysql_stmt_fetch(res->statement);
        switch (ret) {
        case 1:
            ret = mysql_stmt_errno(res->statement);
            break;
        case MYSQL_NO_DATA:
            ret = -1;
            break;
        default:
            ret = 0; /* bad luck - get_entry will deal with this */
            break;
        }
    }
    else {
        if (res->random) {
            if (rownum > 0) {
                mysql_data_seek(res->res, (my_ulonglong) --rownum);
            }
            else {
                return -1; /* invalid row */
            }
        }
        r = mysql_fetch_row(res->res);
        if (r == NULL) {
            ret = -1;
        }
    }
    if (ret == 0) {
        if (!*row) {
            *row = apr_palloc(pool, sizeof(apr_dbd_row_t));
        }
        (*row)->row = r;
        (*row)->res = res;
        (*row)->len = mysql_fetch_lengths(res->res);
    }
    else {
        apr_pool_cleanup_run(res->pool, res->res, free_result);
    }
    return ret;
}