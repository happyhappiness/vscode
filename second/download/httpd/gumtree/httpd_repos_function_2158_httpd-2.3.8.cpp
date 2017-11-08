static apr_status_t slotmem_create(ap_slotmem_instance_t **new,
                                   const char *name, apr_size_t item_size,
                                   unsigned int item_num,
                                   ap_slotmem_type_t type, apr_pool_t *pool)
{
/*    void *slotmem = NULL; */
    void *ptr;
    sharedslotdesc_t desc;
    ap_slotmem_instance_t *res;
    ap_slotmem_instance_t *next = globallistmem;
    const char *fname;
    apr_shm_t *shm;
    apr_size_t basesize = (item_size * item_num);
    apr_size_t size = sizeof(sharedslotdesc_t) +
                      (item_num * sizeof(char)) + basesize;
    apr_status_t rv;

    if (gpool == NULL)
        return APR_ENOSHMAVAIL;
    if (name) {
        if (name[0] == ':') {
            fname = name;
        }
        else {
            fname = ap_server_root_relative(pool, name);
        }

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
    else {
        fname = "anonymous";
    }

    /* first try to attach to existing shared memory */
    if (name && name[0] != ':') {
        rv = apr_shm_attach(&shm, fname, gpool);
    }
    else {
        rv = APR_EINVAL;
    }
    if (rv == APR_SUCCESS) {
        /* check size */
        if (apr_shm_size_get(shm) != size) {
            apr_shm_detach(shm);
            return APR_EINVAL;
        }
        ptr = apr_shm_baseaddr_get(shm);
        memcpy(&desc, ptr, sizeof(desc));
        if (desc.size != item_size || desc.num != item_num) {
            apr_shm_detach(shm);
            return APR_EINVAL;
        }
        ptr = ptr + sizeof(desc);
    }
    else {
        apr_size_t dsize = size - sizeof(sharedslotdesc_t);
        if (name && name[0] != ':') {
            apr_shm_remove(fname, gpool);
            rv = apr_shm_create(&shm, size, fname, gpool);
        }
        else {
            rv = apr_shm_create(&shm, size, NULL, gpool);
        }
        if (rv != APR_SUCCESS) {
            return rv;
        }
        if (name && name[0] != ':') {
            /* Set permissions to shared memory
             * so it can be attached by child process
             * having different user credentials
             *
             * See apr:shmem/unix/shm.c
             */
            unixd_set_shm_perms(fname);
        }
        ptr = apr_shm_baseaddr_get(shm);
        desc.size = item_size;
        desc.num = item_num;
        desc.type = type;
        memcpy(ptr, &desc, sizeof(desc));
        ptr = ptr + sizeof(desc);
        memset(ptr, 0, dsize);
        /*
         * TODO: Error check the below... What error makes
         * sense if the restore fails? Any?
         */
        if (type & AP_SLOTMEM_TYPE_PERSIST)
            restore_slotmem(ptr, fname, dsize, pool);
    }

    /* For the chained slotmem stuff */
    res = (ap_slotmem_instance_t *) apr_pcalloc(gpool,
                                                sizeof(ap_slotmem_instance_t));
    res->name = apr_pstrdup(gpool, fname);
    res->shm = shm;
    res->base = ptr;
    res->desc = desc;
    res->gpool = gpool;
    res->next = NULL;
    res->inuse = ptr + basesize;
    if (globallistmem == NULL) {
        globallistmem = res;
    }
    else {
        next->next = res;
    }

    *new = res;
    return APR_SUCCESS;
}