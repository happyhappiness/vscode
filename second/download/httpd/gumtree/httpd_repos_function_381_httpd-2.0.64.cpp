static apr_array_header_t *parse_log_string(apr_pool_t *p, const char *s, const char **err)
{
    apr_array_header_t *a = apr_array_make(p, 30, sizeof(log_format_item));
    char *res;

    while (*s) {
        if ((res = parse_log_item(p, (log_format_item *) apr_array_push(a), &s))) {
            *err = res;
            return NULL;
        }
    }

    s = APR_EOL_STR;
    parse_log_item(p, (log_format_item *) apr_array_push(a), &s);
    return a;
}