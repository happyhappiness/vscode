static const char *dbd_sqlite_get_entry(const apr_dbd_row_t * row, int n)
{
    return row->data[n];
}