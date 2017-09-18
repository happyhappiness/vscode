		"</STRONG>", NULL));

    /* Allow "error-notes" string to be printed by ap_send_error_response() */
    apr_table_setn(r->notes, "verbose-error-to", apr_pstrdup(r->pool, "*"));

    r->status_line = apr_psprintf(r->pool, "%3.3u Proxy Error", statuscode);
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
			 "proxy: %s returned by %s", message, r->uri);
    return statuscode;
}

static const char *
     proxy_get_host_of_request(request_rec *r)
