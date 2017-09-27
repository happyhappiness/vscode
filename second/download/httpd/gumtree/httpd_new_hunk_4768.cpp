static int proxy_match_word(struct dirconn_entry *This, request_rec *r)
{
    const char *host = proxy_get_host_of_request(r);
    return host != NULL && ap_strstr_c(host, This->name) != NULL;
}

/* Backwards-compatible interface. */
PROXY_DECLARE(int) ap_proxy_checkproxyblock(request_rec *r, proxy_server_conf *conf,
                             apr_sockaddr_t *uri_addr)
{
    return ap_proxy_checkproxyblock2(r, conf, uri_addr->hostname, uri_addr);
}

#define MAX_IP_STR_LEN (46)

PROXY_DECLARE(int) ap_proxy_checkproxyblock2(request_rec *r, proxy_server_conf *conf,
                                             const char *hostname, apr_sockaddr_t *addr)
{
    int j;

    /* XXX FIXME: conf->noproxies->elts is part of an opaque structure */
    for (j = 0; j < conf->noproxies->nelts; j++) {
        struct noproxy_entry *npent = (struct noproxy_entry *) conf->noproxies->elts;
        struct apr_sockaddr_t *conf_addr;

        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                      "checking remote machine [%s] against [%s]",
                      hostname, npent[j].name);
        if (ap_strstr_c(hostname, npent[j].name) || npent[j].name[0] == '*') {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(00916)
                          "connect to remote machine %s blocked: name %s "
                          "matched", hostname, npent[j].name);
            return HTTP_FORBIDDEN;
        }

        /* No IP address checks if no IP address was passed in,
         * i.e. the forward address proxy case, where this server does
         * not resolve the hostname.  */
        if (!addr)
            continue;

        for (conf_addr = npent[j].addr; conf_addr; conf_addr = conf_addr->next) {
            char caddr[MAX_IP_STR_LEN], uaddr[MAX_IP_STR_LEN];
            apr_sockaddr_t *uri_addr;

            if (apr_sockaddr_ip_getbuf(caddr, sizeof caddr, conf_addr))
                continue;

            for (uri_addr = addr; uri_addr; uri_addr = uri_addr->next) {
                if (apr_sockaddr_ip_getbuf(uaddr, sizeof uaddr, uri_addr))
                    continue;
                ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                              "ProxyBlock comparing %s and %s", caddr, uaddr);
                if (!strcmp(caddr, uaddr)) {
                    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(00917)
                                  "connect to remote machine %s blocked: "
                                  "IP %s matched", hostname, caddr);
                    return HTTP_FORBIDDEN;
                }
            }
        }
    }

    return OK;
}

/* set up the minimal filter set */
PROXY_DECLARE(int) ap_proxy_pre_http_request(conn_rec *c, request_rec *r)
{
