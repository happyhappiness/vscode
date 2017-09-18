
    /* Look up entity keyed to 'url' */
    if (strcasecmp(type, "disk")) {
	return DECLINED;
    }

    /* Open the data file */
    rc = apr_file_open(&fd, data, APR_READ|APR_BINARY, 0, r->pool);
    if (rc != APR_SUCCESS) {
        /* XXX: Log message */
        return DECLINED;
    }
