
/*
 * NOTICE: if you tweak this you should look at is_empty_table() 
 * and table_elts() in alloc.h
 */
#ifdef MAKE_TABLE_PROFILE
static apr_table_entry_t *table_push(apr_table_t *t)
{
    if (t->a.nelts == t->a.nalloc) {
        return NULL;
    }
    return (apr_table_entry_t *) apr_array_push_noclear(&t->a);
}
#else /* MAKE_TABLE_PROFILE */
#define table_push(t)	((apr_table_entry_t *) apr_array_push_noclear(&(t)->a))
#endif /* MAKE_TABLE_PROFILE */

APR_DECLARE(const apr_array_header_t *) apr_table_elts(const apr_table_t *t)
{
