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
static apr_status_t write_body(cache_handle_t *h, request_rec *r, apr_bucket_brigade *b) 
{
    apr_bucket *e;
    apr_status_t rv;
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;

    if (!dobj->fd) {
        rv = apr_file_open(&dobj->fd, dobj->tempfile, 
                           APR_WRITE | APR_CREATE | APR_BINARY| APR_TRUNCATE | APR_BUFFERED,
                           APR_UREAD | APR_UWRITE, r->pool);
        if (rv != APR_SUCCESS) {
            return rv;
        }
    }
    APR_BRIGADE_FOREACH(e, b) {
        const char *str;
        apr_size_t length;
        apr_bucket_read(e, &str, &length, APR_BLOCK_READ);
        apr_file_write(dobj->fd, str, &length);
    }
    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(b))) {
        file_cache_el_final(h, r);    /* Link to the perm file, and close the descriptor  */
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                     "disk_cache: Cached body for URL %s",  dobj->name);
    }

    return APR_SUCCESS;	
}

static void *create_config(apr_pool_t *p, server_rec *s)
{
    disk_cache_conf *conf = apr_pcalloc(p, sizeof(disk_cache_conf));

