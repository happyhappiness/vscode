static int add_trailers(void *data, const char *key, const char *val)
{
    if (val) {
        apr_table_add((apr_table_t*)data, key, val);
    }
    return 1;
}