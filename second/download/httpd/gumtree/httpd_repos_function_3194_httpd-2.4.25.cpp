static apr_status_t slotmem_create(ap_slotmem_instance_t **new, const char *name, apr_size_t item_size, unsigned int item_num, ap_slotmem_type_t type, apr_pool_t *pool)
{
    ap_slotmem_instance_t *res;
    ap_slotmem_instance_t *next = globallistmem;
    apr_size_t basesize = (item_size * item_num);

    const char *fname;

    if (name) {
        if (name[0] == ':')
            fname = name;
        else
            fname = ap_runtime_dir_relative(pool, name);

        /* first try to attach to existing slotmem */
        if (next) {
            for (;;) {
                if (strcmp(next->name, fname) == 0) {
                    /* we already have it */
                    *new = next;
                    return APR_SUCCESS;
                }
                if (!next->next) {
                     break;
                }
                next = next->next;
            }
        }
    }
    else
        fname = "anonymous";

    /* create the memory using the gpool */
    res = (ap_slotmem_instance_t *) apr_pcalloc(gpool, sizeof(ap_slotmem_instance_t));
    res->base = apr_pcalloc(gpool, basesize + (item_num * sizeof(char)));
    if (!res->base)
        return APR_ENOSHMAVAIL;

    /* For the chained slotmem stuff */
    res->name = apr_pstrdup(gpool, fname);
    res->size = item_size;
    res->num = item_num;
    res->next = NULL;
    res->type = type;
    res->inuse = (char *)res->base + basesize;
    if (globallistmem == NULL)
        globallistmem = res;
    else
        next->next = res;

    *new = res;
    return APR_SUCCESS;
}