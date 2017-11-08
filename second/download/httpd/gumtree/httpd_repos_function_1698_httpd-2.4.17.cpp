static void push_item(apr_array_header_t *arr, char *type, const char *to,
                      const char *path, const char *data)
{
    struct item *p = (struct item *) apr_array_push(arr);

    if (!to) {
        to = "";
    }
    if (!path) {
        path = "";
    }

    p->type = type;
    p->data = apr_pstrdup(arr->pool, data);
    p->apply_path = apr_pstrcat(arr->pool, path, "*", NULL);

    if ((type == BY_PATH) && (!ap_is_matchexp(to))) {
        p->apply_to = apr_pstrcat(arr->pool, "*", to, NULL);
    }
    else if (to) {
        p->apply_to = apr_pstrdup(arr->pool, to);
    }
    else {
        p->apply_to = NULL;
    }
}