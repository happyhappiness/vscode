static int edit_header(void *v, const char *key, const char *val)
{
    edit_do *ed = (edit_do *)v;

    apr_table_addn(ed->t, key, process_regexp(ed->hdr, val, ed->p));
    return 1;
}