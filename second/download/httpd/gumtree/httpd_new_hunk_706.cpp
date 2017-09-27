
    *newch = (unsigned char *) apr_palloc(r->pool, n);
    rv = apr_file_read(pipe_out, *newch, &n);
    if (n == 0) {
	apr_pool_destroy(sub_context);
	ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
            MODNAME ": read failed from uncompress of %s", r->filename);
	return -1;
    }
    apr_pool_destroy(sub_context);
    return n;
}

