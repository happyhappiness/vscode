static int add_header(void *table, const char *n, const char *v)
{
    apr_table_addn(table, n, v);
    return 1;
}