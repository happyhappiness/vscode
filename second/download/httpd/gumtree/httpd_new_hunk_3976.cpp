                               (long int)getpid());

    /* Now create that segment */
    rs = apr_shm_create(&exipc_shm, sizeof(exipc_data),
                        (const char *) shmfilename, pconf);
    if (APR_SUCCESS != rs) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rs, s, APLOGNO(02993)
                     "Failed to create shared memory segment on file %s",
                     shmfilename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* Created it, now let's zero it out */
