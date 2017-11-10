static apr_array_header_t *get_sorted_modules(apr_pool_t *p)
{
    apr_array_header_t *arr = apr_array_make(p, 64, sizeof(module *));
    module *modp, **entry;
    for (modp = ap_top_module; modp; modp = modp->next) {
        entry = &APR_ARRAY_PUSH(arr, module *);
        *entry = modp;
    }
    qsort(arr->elts, arr->nelts, sizeof(module *), cmp_module_name);
    return arr;
}