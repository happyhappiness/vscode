static int find_conn_headers(void *data, const char *key, const char *val)
{
    header_connection *x = data;
    const char *name;

    do {
        while (*val == ',') {
            val++;
        }
        name = ap_get_token(x->pool, &val, 0);
        if (!strcasecmp(name, "close")) {
            x->closed = 1;
        }
        if (!x->first) {
            x->first = name;
        }
        else {
            const char **elt;
            if (!x->array) {
                x->array = apr_array_make(x->pool, 4, sizeof(char *));
            }
            elt = apr_array_push(x->array);
            *elt = name;
        }
    } while (*val);

    return 1;
}