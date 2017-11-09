static int add_them_all(void *v, const char *key, const char *val)
{
    apr_table_t *headers = (apr_table_t *)v;

    apr_table_addn(headers, key, val);
    return 1;
}