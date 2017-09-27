    apr_shm_t *shm;
    apr_status_t rv;

    if (gpool == NULL) {
        return APR_ENOSHMAVAIL;
    }
    if (name) {
        if (name[0] == ':') {
            fname = name;
        }
        else {
            fname = ap_server_root_relative(pool, name);
        }
    }
    else {
        return APR_ENOSHMAVAIL;
    }

    /* first try to attach to existing slotmem */
    if (next) {
        for (;;) {
            if (strcmp(next->name, fname) == 0) {
                /* we already have it */
                *new = next;
                *item_size = next->desc.size;
                *item_num = next->desc.num;
                return APR_SUCCESS;
            }
            if (!next->next) {
                 break;
            }
            next = next->next;
        }
    }

    /* first try to attach to existing shared memory */
    rv = apr_shm_attach(&shm, fname, gpool);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    /* Read the description of the slotmem */
