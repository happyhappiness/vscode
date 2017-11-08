static BOOL ssl_expr_eval_oid(request_rec *r, const char *word, const char *oidstr)
{
    int j;
    BOOL result = FALSE;
    apr_array_header_t *oid_array;
    char **oid_value;

    if (NULL == (oid_array = ssl_ext_list(r->pool, r->connection, 1, oidstr))) {
        return FALSE;
    }

    oid_value = (char **) oid_array->elts;
    for (j = 0; j < oid_array->nelts; j++) {
        if (strcmp(word, oid_value[j]) == 0) {
            result = TRUE;
            break;
        }
    }
    return result;
}