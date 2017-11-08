static apr_status_t slotmem_create(ap_slotmem_instance_t **new,
                                   const char *name, apr_size_t item_size,
                                   unsigned int item_num,
                                   ap_slotmem_type_t type, apr_pool_t *pool)
{
/*    void *slotmem = NULL; */
    int fbased = 1;
    int restored = 0;
    char *ptr;
    sharedslotdesc_t desc;
    ap_slotmem_instance_t *res;
    ap_slotmem_instance_t *next = globallistmem;
    const char *fname;
    apr_shm_t *shm;
    apr_size_t basesize = (item_size * item_num);
    apr_size_t size = AP_SLOTMEM_OFFSET + AP_UNSIGNEDINT_OFFSET +
                      (item_num * sizeof(char)) + basesize;
    apr_status_t rv;

    if (gpool == NULL) {
        return APR_ENOSHMAVAIL;
    }
    fname = slotmem_filename(pool, name, 0);
    if (fname) {
        /* first try to attach to existing slotmem */
        if (next) {
            for (;;) {
                if (strcmp(next->name, fname) == 0) {
                    /* we already have it */
                    *new = next;
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02603)
                                 "create found %s in global list", fname);
                    return APR_SUCCESS;
                }
                if (!next->next) {
                     break;
                }
                next = next->next;
            }
        }
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02602)
                     "create didn't find %s in global list", fname);
    }
    else {
        fbased = 0;
        fname = "none";
    }

    /* first try to attach to existing shared memory */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02300)
                 "create %s: %"APR_SIZE_T_FMT"/%u", fname, item_size,
                 item_num);
    if (fbased) {
        rv = apr_shm_attach(&shm, fname, gpool);
    }
    else {
        rv = APR_EINVAL;
    }
    if (rv == APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02598)
                     "apr_shm_attach() succeeded");

        /* check size */
        if (apr_shm_size_get(shm) != size) {
            apr_shm_detach(shm);
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(02599)
                         "existing shared memory for %s could not be used (failed size check)",
                         fname);
            return APR_EINVAL;
        }
        ptr = (char *)apr_shm_baseaddr_get(shm);
        memcpy(&desc, ptr, sizeof(desc));
        if (desc.size != item_size || desc.num != item_num) {
            apr_shm_detach(shm);
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(02600)
                         "existing shared memory for %s could not be used (failed contents check)",
                         fname);
            return APR_EINVAL;
        }
        ptr += AP_SLOTMEM_OFFSET;
    }
    else {
        apr_size_t dsize = size - AP_SLOTMEM_OFFSET;
        if (fbased) {
            apr_shm_remove(fname, gpool);
            rv = apr_shm_create(&shm, size, fname, gpool);
        }
        else {
            rv = apr_shm_create(&shm, size, NULL, gpool);
        }
        ap_log_error(APLOG_MARK, rv == APR_SUCCESS ? APLOG_DEBUG : APLOG_ERR,
                     rv, ap_server_conf, APLOGNO(02611)
                     "create: apr_shm_create(%s) %s",
                     fname ? fname : "",
                     rv == APR_SUCCESS ? "succeeded" : "failed");
        if (rv != APR_SUCCESS) {
            return rv;
        }
        if (fbased) {
            /* Set permissions to shared memory
             * so it can be attached by child process
             * having different user credentials
             *
             * See apr:shmem/unix/shm.c
             */
            unixd_set_shm_perms(fname);
        }
        ptr = (char *)apr_shm_baseaddr_get(shm);
        desc.size = item_size;
        desc.num = item_num;
        desc.type = type;
        memcpy(ptr, &desc, sizeof(desc));
        ptr += AP_SLOTMEM_OFFSET;
        memset(ptr, 0, dsize);
        /*
         * TODO: Error check the below... What error makes
         * sense if the restore fails? Any?
         */
        if (type & AP_SLOTMEM_TYPE_PERSIST) {
            rv = restore_slotmem(ptr, fname, dsize, pool);
            if (rv == APR_SUCCESS) {
                restored = 1;
            }
            else {
                /* just in case, re-zero */
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                             APLOGNO(02554) "could not restore %s", fname);
                memset(ptr, 0, dsize);
            }
        }
    }

    /* For the chained slotmem stuff */
    res = (ap_slotmem_instance_t *) apr_pcalloc(gpool,
                                                sizeof(ap_slotmem_instance_t));
    res->name = apr_pstrdup(gpool, fname);
    res->fbased = fbased;
    res->shm = shm;
    res->num_free = (unsigned int *)ptr;
    if (!restored) {
        *res->num_free = item_num;
    }
    res->persist = (void *)ptr;
    ptr += AP_UNSIGNEDINT_OFFSET;
    res->base = (void *)ptr;
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