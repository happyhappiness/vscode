static int proxy_match_word(struct dirconn_entry *This, request_rec *r)
{
    const char *host = proxy_get_host_of_request(r);
    return host != NULL && ap_strstr_c(host, This->name) != NULL;
}

/* checks whether a host in uri_addr matches proxyblock */
PROXY_DECLARE(int) ap_proxy_checkproxyblock(request_rec *r, proxy_server_conf *conf,
                             apr_sockaddr_t *uri_addr)
{
    int j;
    apr_sockaddr_t * src_uri_addr = uri_addr;
    /* XXX FIXME: conf->noproxies->elts is part of an opaque structure */
    for (j = 0; j < conf->noproxies->nelts; j++) {
        struct noproxy_entry *npent = (struct noproxy_entry *) conf->noproxies->elts;
        struct apr_sockaddr_t *conf_addr = npent[j].addr;
        uri_addr = src_uri_addr;
        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                      "checking remote machine [%s] against [%s]",
                      uri_addr->hostname, npent[j].name);
        if (ap_strstr_c(uri_addr->hostname, npent[j].name)
            || npent[j].name[0] == '*') {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(00916)
                          "connect to remote machine %s blocked: name %s "
                          "matched", uri_addr->hostname, npent[j].name);
            return HTTP_FORBIDDEN;
        }
        while (conf_addr) {
            uri_addr = src_uri_addr;
            while (uri_addr) {
                char *conf_ip;
                char *uri_ip;
                apr_sockaddr_ip_get(&conf_ip, conf_addr);
                apr_sockaddr_ip_get(&uri_ip, uri_addr);
                ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                              "ProxyBlock comparing %s and %s", conf_ip,
                              uri_ip);
                if (!apr_strnatcasecmp(conf_ip, uri_ip)) {
                    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(00917)
                                 "connect to remote machine %s blocked: "
                                 "IP %s matched", uri_addr->hostname, conf_ip);
                    return HTTP_FORBIDDEN;
                }
                uri_addr = uri_addr->next;
            }
            conf_addr = conf_addr->next;
        }
    }
    return OK;
}

/* set up the minimal filter set */
PROXY_DECLARE(int) ap_proxy_pre_http_request(conn_rec *c, request_rec *r)
{
