static const char *dbd_freetds_get_entry(const apr_dbd_row_t *row, int n)
{
    /* FIXME: support different data types */
    /* this fails - bind gets some vars but not others
    return (const char*)row->res->vars[n].data;
     */
    DBPROCESS* proc = row->res->proc;
    BYTE *ptr = dbdata(proc, n+1);
    int t = dbcoltype(proc, n+1);
    int l = dbcollen(proc, n+1);
    if (dbwillconvert(t, SYBCHAR)) {
      dbconvert(proc, t, ptr, l, SYBCHAR, (BYTE *)row->buf, -1);
      return (const char*)row->buf;
    }
    return (char*)ptr;
}