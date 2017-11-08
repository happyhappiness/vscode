static int
dialup_handler(request_rec *r)
{
    int status;
    apr_status_t rv;
    dialup_dcfg_t *dcfg;
    core_dir_config *ccfg;
    apr_file_t *fd;
    dialup_baton_t *db;
    apr_bucket *e;


    /* See core.c, default handler for all of the cases we just decline. */
    if (r->method_number != M_GET || 
        r->finfo.filetype == 0 || 
        r->finfo.filetype == APR_DIR) {
        return DECLINED;
    }

    dcfg = ap_get_module_config(r->per_dir_config,
                                &dialup_module);

    if (dcfg->bytes_per_second == 0) {
        return DECLINED;
    }

    ccfg = ap_get_module_config(r->per_dir_config,
                                &core_module);


    rv = apr_file_open(&fd, r->filename, APR_READ | APR_BINARY
#if APR_HAS_SENDFILE
                           | ((ccfg->enable_sendfile == ENABLE_SENDFILE_OFF)
                              ? 0 : APR_SENDFILE_ENABLED)
#endif
                       , 0, r->pool);

    if (rv) {
        return DECLINED;
    }

    /* copied from default handler: */
    ap_update_mtime(r, r->finfo.mtime);
    ap_set_last_modified(r);
    ap_set_etag(r);
    apr_table_setn(r->headers_out, "Accept-Ranges", "bytes");
    ap_set_content_length(r, r->finfo.size);

    status = ap_meets_conditions(r);
    if (status != OK) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "dialup: declined, meets conditions, good luck core handler");
        return DECLINED;
    }

    db = apr_palloc(r->pool, sizeof(dialup_baton_t));
    
    db->bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    db->tmpbb = apr_brigade_create(r->pool, r->connection->bucket_alloc);

    e = apr_brigade_insert_file(db->bb, fd, 0, r->finfo.size, r->pool);

#if APR_HAS_MMAP
    if (ccfg->enable_mmap == ENABLE_MMAP_OFF) {
        apr_bucket_file_enable_mmap(e, 0);
    }
#endif
    
    
    db->bytes_per_second = dcfg->bytes_per_second;
    db->r = r;
    db->fd = fd;

    e = apr_bucket_eos_create(r->connection->bucket_alloc);

    APR_BRIGADE_INSERT_TAIL(db->bb, e);

    status = dialup_send_pulse(db);
    if (status != SUSPENDED && status != DONE) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "dialup: failed, send pulse");
        return status;
    }

    ap_mpm_register_timed_callback(apr_time_from_sec(1), dialup_callback, db);

    return SUSPENDED;
}