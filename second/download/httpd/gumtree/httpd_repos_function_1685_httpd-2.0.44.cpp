static const char *hdr(const apr_table_t *tbl, const char *name)
{
    const char *val = apr_table_get(tbl, name);
    if (val) {
        return val;
    }
    else {
        return "";
    }
}