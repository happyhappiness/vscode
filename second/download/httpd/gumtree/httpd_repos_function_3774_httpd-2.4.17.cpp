static void add_unless_null(apr_table_t *table, const char *name, const char *val)
{
    if (name && val) {
        apr_table_addn(table, name, val);
    }
}