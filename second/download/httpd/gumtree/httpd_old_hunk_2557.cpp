        apr_shm_remove(ctx->data_file, p);

        rv = apr_shm_create(&ctx->shm, ctx->shm_size, ctx->data_file, p);
    }

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Could not allocate shared memory segment for shmcb "
                     "socache");
        return rv;
    }

    shm_segment = apr_shm_baseaddr_get(ctx->shm);
    shm_segsize = apr_shm_size_get(ctx->shm);
    if (shm_segsize < (5 * sizeof(SHMCBHeader))) {
        /* the segment is ridiculously small, bail out */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shared memory segment too small");
        return APR_ENOSPC;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "shmcb_init allocated %" APR_SIZE_T_FMT
                 " bytes of shared memory",
                 shm_segsize);
    /* Discount the header */
    shm_segsize -= sizeof(SHMCBHeader);
    /* Select index size based on average object size hints, if given. */
