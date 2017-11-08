static int dbd_sqlite3_select_internal(apr_pool_t *pool,
                                       apr_dbd_t *sql,
                                       apr_dbd_results_t **results,
                                       sqlite3_stmt *stmt, int seek)
{
    int ret, retry_count = 0, column_count;
    size_t i, num_tuples = 0;
    int increment = 0;
    apr_dbd_row_t *row = NULL;
    apr_dbd_row_t *lastrow = NULL;
    apr_dbd_column_t *column;
    char *hold = NULL;

    column_count = sqlite3_column_count(stmt);
    if (!*results) {
        *results = apr_pcalloc(pool, sizeof(apr_dbd_results_t));
    }
    (*results)->stmt = stmt;
    (*results)->sz = column_count;
    (*results)->random = seek;
    (*results)->next_row = 0;
    (*results)->tuples = 0;
    (*results)->col_names = apr_pcalloc(pool, column_count * sizeof(char *));
    (*results)->pool = pool;
    do {
        ret = sqlite3_step(stmt);
        if (ret == SQLITE_BUSY) {
            if (retry_count++ > MAX_RETRY_COUNT) {
                ret = SQLITE_ERROR;
            } else {
                apr_dbd_mutex_unlock();
                apr_sleep(MAX_RETRY_SLEEP);
                apr_dbd_mutex_lock();
            }
        } else if (ret == SQLITE_ROW) {
            int length;
            row = apr_palloc(pool, sizeof(apr_dbd_row_t));
            row->res = *results;
            increment = sizeof(apr_dbd_column_t *);
            length = increment * (*results)->sz;
            row->columns = apr_palloc(pool, length);
            row->columnCount = column_count;
            for (i = 0; i < (*results)->sz; i++) {
                column = apr_palloc(pool, sizeof(apr_dbd_column_t));
                row->columns[i] = column;
                /* copy column name once only */
                if ((*results)->col_names[i] == NULL) {
                    (*results)->col_names[i] =
                        apr_pstrdup(pool, sqlite3_column_name(stmt, i));
                }
                column->name = (*results)->col_names[i];
                column->size = sqlite3_column_bytes(stmt, i);
                column->type = sqlite3_column_type(stmt, i);
                column->value = NULL;
                switch (column->type) {
                case SQLITE_FLOAT:
                case SQLITE_INTEGER:
                case SQLITE_TEXT:
                    hold = (char *) sqlite3_column_text(stmt, i);
                    if (hold) {
                        column->value = apr_pstrmemdup(pool, hold,
                                                       column->size);
                    }
                    break;
                case SQLITE_BLOB:
                    hold = (char *) sqlite3_column_blob(stmt, i);
                    if (hold) {
                        column->value = apr_pstrmemdup(pool, hold,
                                                       column->size);
                    }
                    break;
                case SQLITE_NULL:
                    break;
                }
            }
            row->rownum = num_tuples++;
            row->next_row = 0;
            (*results)->tuples = num_tuples;
            if ((*results)->next_row == 0) {
                (*results)->next_row = row;
            }
            if (lastrow != 0) {
                lastrow->next_row = row;
            }
            lastrow = row;
        }
    } while (ret == SQLITE_ROW || ret == SQLITE_BUSY);

    if (dbd_sqlite3_is_success(ret)) {
        ret = 0;
    }
    return ret;
}