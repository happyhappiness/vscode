static apr_status_t write_headers(cache_handle_t *h, request_rec *r, cache_info *info)
{
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config, 
                                                 &disk_cache_module);
    apr_status_t rv;
    char *buf;
    char statusbuf[8];
    apr_size_t amt;
    disk_cache_object_t *dobj = (disk_cache_object_t*) h->cache_obj->vobj;
    apr_file_t *hfd = dobj->hfd;

    if (!hfd)  {
        if (!dobj->hdrsfile) {
            dobj->hdrsfile = header_file(r->pool, 
                                         conf->dirlevels, 
                                         conf->dirlength, 
                                         conf->cache_root,
                                         h->cache_obj->key);
        }
        
        /* This is flaky... we need to manage the cache_info differently */
        h->cache_obj->info = *info;
        
        /* Remove old file with the same name. If remove fails, then
         * perhaps we need to create the directory tree where we are
         * about to write the new headers file.
         */
        rv = apr_file_remove(dobj->hdrsfile, r->pool);
        if (rv != APR_SUCCESS) {
            mkdir_structure(conf, dobj->hdrsfile, r->pool);
        }

        rv = apr_file_open(&dobj->hfd, dobj->hdrsfile,
                           APR_WRITE | APR_CREATE | APR_EXCL,
                           APR_OS_DEFAULT, r->pool);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        hfd = dobj->hfd;
        dobj->name = h->cache_obj->key;

        file_cache_write_mydata(dobj->hfd, h, r);

        if (r->headers_out) {
            int i;
            apr_table_t* headers_out = ap_cache_cacheable_hdrs_out(r->pool, r->headers_out);
            apr_table_entry_t *elts = (apr_table_entry_t *) apr_table_elts(headers_out)->elts;
            for (i = 0; i < apr_table_elts(headers_out)->nelts; ++i) {
                if (elts[i].key != NULL) {
                    buf = apr_pstrcat(r->pool, elts[i].key, ": ",  elts[i].val, CRLF, NULL);
                    amt = strlen(buf);
                    apr_file_write(hfd, buf, &amt);
                }
            }
            buf = apr_pstrcat(r->pool, CRLF, NULL);
            amt = strlen(buf);
            apr_file_write(hfd, buf, &amt);
            
            /* This case only occurs when the content is generated locally */
            if (!apr_table_get(r->headers_out, "Content-Type") && r->content_type) {
                apr_table_setn(r->headers_out, "Content-Type", 
                               ap_make_content_type(r, r->content_type));
            }
        }
        sprintf(statusbuf,"%d", r->status);
        buf = apr_pstrcat(r->pool, statusbuf, CRLF, NULL);
        amt = strlen(buf);
        apr_file_write(hfd, buf, &amt);

        /* This case only occurs when the content is generated locally */
        if (!r->status_line) {
            r->status_line = ap_get_status_line(r->status);
        }
        buf = apr_pstrcat(r->pool, r->status_line, "\n", NULL);
        amt = strlen(buf);
        apr_file_write(hfd, buf, &amt);
        buf = apr_pstrcat(r->pool, CRLF, NULL);
        amt = strlen(buf);
        apr_file_write(hfd, buf, &amt);

	/* Parse the vary header and dump those fields from the headers_in. */
	/* Make call to the same thing cache_select_url calls to crack Vary. */
	/* @@@ Some day, not today. */
        if (r->headers_in) {
            int i;
            apr_table_entry_t *elts = (apr_table_entry_t *) apr_table_elts(r->headers_in)->elts;
            for (i = 0; i < apr_table_elts(r->headers_in)->nelts; ++i) {
                if (elts[i].key != NULL) {
                    buf = apr_pstrcat(r->pool, elts[i].key, ": ",  elts[i].val, CRLF, NULL);
                    amt = strlen(buf);
                    apr_file_write(hfd, buf, &amt);
                }
            }
            buf = apr_pstrcat(r->pool, CRLF, NULL);
            amt = strlen(buf);
            apr_file_write(hfd, buf, &amt);
        }
        apr_file_close(hfd); /* flush and close */
    }
    else {
        /* XXX log message */
    }

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "disk_cache: Caching headers for URL %s",  dobj->name);
    return APR_SUCCESS;
}