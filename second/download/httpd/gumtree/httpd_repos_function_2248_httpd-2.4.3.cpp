static apr_status_t slotmem_attach(ap_slotmem_instance_t **new,
                                   const char *name, apr_size_t *item_size,
                                   unsigned int *item_num, apr_pool_t *pool)
{
/*    void *slotmem = NULL; */
    char *ptr;
    ap_slotmem_instance_t *res;
    ap_slotmem_instance_t *next = globallistmem;
    sharedslotdesc_t desc;
    const char *fname;
    apr_shm_t *shm;
    apr_status_t rv;

    if (gpool == NULL) {
        return APR_ENOSHMAVAIL;
    }
    fname = slotmem_filename(pool, name);
    if (!fname) {
        return APR_ENOSHMAVAIL;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02301)
                 "attach looking for %s", fname);

    /* first try to attach to existing slotmem */
    if (next) {
        for (;;) {
            if (strcmp(next->name, fname) == 0) {
                /* we already have it */
                *new = next;
                *item_size = next->desc.size;
                *item_num = next->desc.num;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                             APLOGNO(02302)
                             "attach found %s: %"APR_SIZE_T_FMT"/%u", fname,
                             *item_size, *item_num);
                return APR_SUCCESS;
            }
            if (!next->next) {
                 break;
            }
            next = next->next;
        }
    }

    /* next try to attach to existing shared memory */
    rv = apr_shm_attach(&shm, fname, gpool);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    /* Read the description of the slotmem */
    ptr = (char *)apr_shm_baseaddr_get(shm);
    memcpy(&desc, ptr, sizeof(desc));
    ptr += AP_SLOTMEM_OFFSET;

    /* For the chained slotmem stuff */
    res = (ap_slotmem_instance_t *) apr_pcalloc(gpool,
                                                sizeof(ap_slotmem_instance_t));
    res->name = apr_pstrdup(gpool, fname);
    res->fbased = 1;
    res->shm = shm;
    res->num_free = (unsigned int *)ptr;
    res->persist = (void *)ptr;
    ptr += AP_UNSIGNEDINT_OFFSET;
    res->base = (void *)ptr;
    res->desc = desc;
    res->gpool = gpool;
    res->inuse = ptr + (desc.size * desc.num);
    res->next = NULL;
    if (globallistmem == NULL) {
        globallistmem = res;
    }
    else {
        next->next = res;
    }

    *new = res;
    *item_size = desc.size;
    *item_num = desc.num;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                 APLOGNO(02303)
                 "attach found %s: %"APR_SIZE_T_FMT"/%u", fname,
                 *item_size, *item_num);
    return APR_SUCCESS;
}