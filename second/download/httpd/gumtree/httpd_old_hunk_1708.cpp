    apr_sockaddr_t * src_uri_addr = uri_addr;
    /* XXX FIXME: conf->noproxies->elts is part of an opaque structure */
    for (j = 0; j < conf->noproxies->nelts; j++) {
        struct noproxy_entry *npent = (struct noproxy_entry *) conf->noproxies->elts;
        struct apr_sockaddr_t *conf_addr = npent[j].addr;
        uri_addr = src_uri_addr;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: checking remote machine [%s] against [%s]", uri_addr->hostname, npent[j].name);
        if ((npent[j].name && ap_strstr_c(uri_addr->hostname, npent[j].name))
            || npent[j].name[0] == '*') {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
                         "proxy: connect to remote machine %s blocked: name %s matched", uri_addr->hostname, npent[j].name);
            return HTTP_FORBIDDEN;
