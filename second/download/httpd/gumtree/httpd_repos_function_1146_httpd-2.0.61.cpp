static int asis_handler(request_rec *r)
{
    conn_rec *c = r->connection;
    apr_file_t *f = NULL;
    apr_status_t rv;
    const char *location;

    if(strcmp(r->handler,ASIS_MAGIC_TYPE) && strcmp(r->handler,"send-as-is"))
	return DECLINED;

    r->allowed |= (AP_METHOD_BIT << M_GET);
    if (r->method_number != M_GET)
	return DECLINED;
    if (r->finfo.filetype == 0) {
	ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
		    "File does not exist: %s", r->filename);
	return HTTP_NOT_FOUND;
    }

    if ((rv = apr_file_open(&f, r->filename, APR_READ, 
                APR_OS_DEFAULT, r->pool)) != APR_SUCCESS) {
	ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
		    "file permissions deny server access: %s", r->filename);
	return HTTP_FORBIDDEN;
    }

    ap_scan_script_header_err(r, f, NULL);
    location = apr_table_get(r->headers_out, "Location");

    if (location && location[0] == '/' &&
	((r->status == HTTP_OK) || ap_is_HTTP_REDIRECT(r->status))) {

	apr_file_close(f);

	/* Internal redirect -- fake-up a pseudo-request */
	r->status = HTTP_OK;

	/* This redirect needs to be a GET no matter what the original
	 * method was.
	 */
	r->method = apr_pstrdup(r->pool, "GET");
	r->method_number = M_GET;

	ap_internal_redirect_handler(location, r);
	return OK;
    }

    if (!r->header_only) {
        apr_bucket_brigade *bb;
        apr_bucket *b;
        apr_off_t pos = 0;

        rv = apr_file_seek(f, APR_CUR, &pos);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "mod_asis: failed to find end-of-headers position "
                          "for %s", r->filename);
            apr_file_close(f);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        bb = apr_brigade_create(r->pool, c->bucket_alloc);
#if APR_HAS_LARGE_FILES
        if (r->finfo.size - pos > AP_MAX_SENDFILE) {
            /* APR_HAS_LARGE_FILES issue; must split into mutiple buckets, 
             * no greater than MAX(apr_size_t), and more granular than that
             * in case the brigade code/filters attempt to read it directly.
             */
            apr_off_t fsize = r->finfo.size - pos;
            b = apr_bucket_file_create(f, pos, AP_MAX_SENDFILE,
                                       r->pool, c->bucket_alloc);
            while (fsize > AP_MAX_SENDFILE) {
                APR_BRIGADE_INSERT_TAIL(bb, b);
                apr_bucket_copy(b, &b);
                b->start += AP_MAX_SENDFILE;
                fsize -= AP_MAX_SENDFILE;
            }
            b->length = (apr_size_t)fsize; /* Resize just the last bucket */
        }
        else
#endif
        b = apr_bucket_file_create(f, pos, (apr_size_t) (r->finfo.size - pos),
                                   r->pool, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        b = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        rv = ap_pass_brigade(r->output_filters, bb);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "mod_asis: ap_pass_brigade failed for file %s", r->filename);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }
    else {
        apr_file_close(f);
    }

    return OK;
}