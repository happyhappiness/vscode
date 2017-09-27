        memset(ptr, 0, dsize);
        /*
         * TODO: Error check the below... What error makes
         * sense if the restore fails? Any?
         */
        if (type & AP_SLOTMEM_TYPE_PERSIST) {
            restore_slotmem(ptr, fname, dsize, pool);
            restored = 1;
        }
    }

    /* For the chained slotmem stuff */
    res = (ap_slotmem_instance_t *) apr_pcalloc(gpool,
                                                sizeof(ap_slotmem_instance_t));
