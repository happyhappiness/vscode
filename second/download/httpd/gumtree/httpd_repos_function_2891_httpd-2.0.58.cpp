static apr_table_entry_t *table_push(apr_table_t *t)
{
    if (t->a.nelts == t->a.nalloc) {
        return NULL;
    }
    return (apr_table_entry_t *) apr_array_push_noclear(&t->a);
}