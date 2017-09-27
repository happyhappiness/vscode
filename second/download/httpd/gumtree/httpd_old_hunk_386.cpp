    r = vr;

    /* sure we got r, but don't call ap_log_rerror() because we don't
     * have r->headers_in and possibly other storage referenced by
     * ap_log_rerror()
     */
    ap_log_error(APLOG_MARK, APLOG_ERR, err, r->server, "%s", description);
}

static int cgid_server(void *data) 
{ 
    struct sockaddr_un unix_addr;
    int sd, sd2, rc;
