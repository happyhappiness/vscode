static const char *dbd_sqlite3_get_entry(const apr_dbd_row_t *row, int n)
{
    apr_dbd_column_t *column;
    const char *value;
    if ((n + 1) > row->columnCount) {
        return NULL;
    }
    column = row->columns[n];
    value = column->value;
    return value;
}