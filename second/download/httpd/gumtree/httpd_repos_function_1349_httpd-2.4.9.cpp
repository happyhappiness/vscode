static int add_header_do(void *v, const char *key, const char *val)
{
    apr_table_addn(v, key, val);
    return 1;
}