static apr_status_t slotmem_attach(ap_slotmem_instance_t **new, const char *name, apr_size_t *item_size, unsigned int *item_num, apr_pool_t *pool)
{
    ap_slotmem_instance_t *next = globallistmem;
    const char *fname;

    if (name) {
        if (name[0] == ':')
            fname = name;
        else
            fname = ap_server_root_relative(pool, name);
    }
    else
        return APR_ENOSHMAVAIL;

    /* first try to attach to existing slotmem */
    while (next) {
        if (strcmp(next->name, fname) == 0) {
            /* we already have it */
            *new = next;
            *item_size = next->size;
            *item_num = next->num;
            return APR_SUCCESS;
        }
        next = next->next;
    }

    return APR_ENOSHMAVAIL;
}