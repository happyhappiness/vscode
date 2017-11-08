static int dbd_sqlite3_pselect(apr_pool_t *pool, apr_dbd_t *sql,
                               apr_dbd_results_t **results,
                               apr_dbd_prepared_t *statement, int seek,
                               int nargs, const char **values)
{
    sqlite3_stmt *stmt = statement->stmt;
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

#if APR_HAS_THREADS
    apr_thread_mutex_lock(sql->mutex);
#endif

    ret = sqlite3_reset(stmt);
    if (ret == SQLITE_OK) {
        int column_count;

        for (i=0; i < nargs; i++) {
            sqlite3_bind_text(stmt, i + 1, values[i], strlen(values[i]),
                              SQLITE_STATIC);
        }

        column_count = sqlite3_column_count(stmt);
        if (!*results) {
            *results = apr_pcalloc(pool, sizeof(apr_dbd_results_t));
        }
        (*results)->stmt = stmt;
        (*results)->sz = column_count;
        (*results)->random = seek;
        (*results)->next_row = 0;
        (*results)->tuples = 0;
        (*results)->col_names = apr_pcalloc(pool,
                                            column_count * sizeof(char *));
        do {
            ret = sqlite3_step(stmt);
            if (ret == SQLITE_BUSY) {
                if (retry_count++ > MAX_RETRY_COUNT) {
                    ret = SQLITE_ERROR;
                } else {
#if APR_HAS_THREADS
                    apr_thread_mutex_unlock(sql->mutex);
#endif
                    apr_sleep(MAX_RETRY_SLEEP);
#if APR_HAS_THREADS
                    apr_thread_mutex_lock(sql->mutex);
#endif
                }
            } else if (ret == SQLITE_ROW) {
                int length;
                apr_dbd_column_t *col;
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
                        hold = NULL;
                        hold = (char *) sqlite3_column_text(stmt, i);
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

        sqlite3_reset(stmt);
    }
#if APR_HAS_THREADS
    apr_thread_mutex_unlock(sql->mutex);
#endif

    if (sql->trans) {
        sql->trans->errnum = ret;
    }
    return ret;
}