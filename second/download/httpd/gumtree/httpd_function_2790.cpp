static apr_table_entry_t *do_table_push(const char *func, apr_table_t *t)
{
    if (t->a.nelts == t->a.nalloc) {
        fprintf(stderr, "%s: table created by %p hit limit of %u\n",
                func ? func : "table_push", t->creator, t->a.nalloc);
    }
    return (apr_table_entry_t *) apr_array_push_noclear(&t->a);
}