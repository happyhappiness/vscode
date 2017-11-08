static int edit_header(void *v, const char *key, const char *val)
{
    edit_do *ed = (edit_do *)v;
    const char *repl = process_regexp(ed->hdr, val, ed->r);
    if (repl == NULL)
        return 0;

    apr_table_addn(ed->t, key, repl);
    return 1;
}