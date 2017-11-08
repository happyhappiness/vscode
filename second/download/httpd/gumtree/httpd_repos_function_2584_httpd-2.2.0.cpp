static int dbd_sqlite3_select(apr_pool_t * pool, apr_dbd_t * sql, apr_dbd_results_t ** results, const char *query, int seek)
{
    sqlite3_stmt *stmt = NULL;
    const char *tail = NULL;
    int i, ret, retry_count = 0;
    size_t num_tuples = 0;
    int increment = 0;
    apr_dbd_row_t *row = NULL;
    apr_dbd_row_t *lastrow = NULL;
    apr_dbd_column_t *column;

    char *hold = NULL;

    if (sql->trans && sql->trans->errnum) {
        return sql->trans->errnum;
    }

    apr_thread_mutex_lock(sql->mutex);

    ret = sqlite3_prepare(sql->conn, query, strlen(query), &stmt, &tail);
    if (!dbd_sqlite3_is_success(ret)) {
        apr_thread_mutex_unlock(sql->mutex);
        return ret;
    } else {
        int column_count;
        column_count = sqlite3_column_count(stmt);
        if (!*results) {
            *results = apr_pcalloc(pool, sizeof(apr_dbd_results_t));
        }
        (*results)->stmt = stmt;
        (*results)->sz = column_count;
        (*results)->random = seek;
        (*results)->next_row = 0;
        (*results)->tuples = 0;
        do {
            ret = sqlite3_step((*results)->stmt);
            if (ret == SQLITE_BUSY) {
                if (retry_count++ > MAX_RETRY_COUNT) {
                    ret = SQLITE_ERROR;
                } else {
                    apr_thread_mutex_unlock(sql->mutex);
                    apr_sleep(MAX_RETRY_SLEEP);
                }
            } else if (ret == SQLITE_ROW) {
                int length;
                apr_dbd_column_t *col;
                row = apr_palloc(pool, sizeof(apr_dbd_row_t));
                row->res = *results;
                row->res->stmt = (*results)->stmt;
                increment = sizeof(apr_dbd_column_t *);
                length = increment * (*results)->sz;
                row->columns = apr_palloc(pool, length);
                row->columnCount = column_count;
                for (i = 0; i < (*results)->sz; i++) {
                    column = apr_palloc(pool, sizeof(apr_dbd_column_t));
                    row->columns[i] = column;
                    column->name = (char *) sqlite3_column_name((*results)->stmt, i);
                    column->size = sqlite3_column_bytes((*results)->stmt, i);
                    column->type = sqlite3_column_type((*results)->stmt, i);
                    switch (column->type) {

                    case SQLITE_FLOAT:
                        break;
                    case SQLITE_INTEGER:
                    case SQLITE_TEXT:
                        hold = NULL;
                        hold = (char *) sqlite3_column_text((*results)->stmt, i);
                        if (hold) {
                            column->value = apr_palloc(pool, column->size + 1);
                            strncpy(column->value, hold, column->size + 1);
                        }
                        break;
                    case SQLITE_BLOB:
                        break;
                    case SQLITE_NULL:
                        break;
                    }
                    col = row->columns[i];
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
            } else if (ret == SQLITE_DONE) {
                ret = SQLITE_OK;
            }
        } while (ret == SQLITE_ROW || ret == SQLITE_BUSY);
    }
    ret = sqlite3_finalize(stmt);
    apr_thread_mutex_unlock(sql->mutex);

    if (sql->trans) {
        sql->trans->errnum = ret;
    }
    return ret;
}