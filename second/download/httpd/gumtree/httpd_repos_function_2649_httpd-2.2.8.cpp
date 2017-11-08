static const char *dbd_sqlite_get_entry(const apr_dbd_row_t * row, int n)
{
    if ((n < 0) || (n >= row->res->sz)) {
      return NULL;
    }

    return row->data[n];
}