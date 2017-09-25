        /* XXX log message */
	return rv;
    }

    r->status = atoi(urlbuff);                           /* Save status line into request rec  */

    rv = apr_file_gets(&urlbuff[0], urllen, dobj->hfd);               /* Read status line */
    if (rv != APR_SUCCESS) {
        /* XXX log message */
	return rv;
    }

    if ((temp = strchr(&urlbuff[0], '\n')) != NULL)       /* trim off new line character */
	*temp = '\0';              /* overlay it with the null terminator */

    r->status_line = apr_pstrdup(r->pool, urlbuff);            /* Save status line into request rec  */

    apr_file_close(dobj->hfd);

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "disk_cache: Served headers for URL %s",  dobj->name);
    return APR_SUCCESS;
}
