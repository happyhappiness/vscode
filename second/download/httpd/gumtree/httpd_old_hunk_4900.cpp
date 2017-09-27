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
