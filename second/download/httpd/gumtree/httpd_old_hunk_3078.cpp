    apr_sockaddr_t * src_uri_addr = uri_addr;
    /* XXX FIXME: conf->noproxies->elts is part of an opaque structure */
    for (j = 0; j < conf->noproxies->nelts; j++) {
        struct noproxy_entry *npent = (struct noproxy_entry *) conf->noproxies->elts;
        struct apr_sockaddr_t *conf_addr = npent[j].addr;
        uri_addr = src_uri_addr;
        ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, r->server,
                     "proxy: checking remote machine [%s] against [%s]", uri_addr->hostname, npent[j].name);
        if ((npent[j].name && ap_strstr_c(uri_addr->hostname, npent[j].name))
            || npent[j].name[0] == '*') {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
                         "proxy: connect to remote machine %s blocked: name %s matched", uri_addr->hostname, npent[j].name);
            return HTTP_FORBIDDEN;
        }
        while (conf_addr) {
            uri_addr = src_uri_addr;
            while (uri_addr) {
                char *conf_ip;
                char *uri_ip;
                apr_sockaddr_ip_get(&conf_ip, conf_addr);
                apr_sockaddr_ip_get(&uri_ip, uri_addr);
                ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, r->server,
                             "proxy: ProxyBlock comparing %s and %s", conf_ip, uri_ip);
                if (!apr_strnatcasecmp(conf_ip, uri_ip)) {
                    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
                                 "proxy: connect to remote machine %s blocked: IP %s matched", uri_addr->hostname, conf_ip);
                    return HTTP_FORBIDDEN;
                }
                uri_addr = uri_addr->next;
            }
            conf_addr = conf_addr->next;
        }
