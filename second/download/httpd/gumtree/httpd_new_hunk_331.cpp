    apr_snprintf(buf1, sizeof(buf1), "%s:password", clientdn);
    ssl_util_uuencode(buf2, buf1, FALSE);

    apr_snprintf(buf1, sizeof(buf1), "Basic %s", buf2);
    apr_table_set(r->headers_in, "Authorization", buf1);

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "Faking HTTP Basic Auth header: \"Authorization: %s\"", buf1);

    return DECLINED;
}

/* authorization phase */
int ssl_hook_Auth(request_rec *r)
