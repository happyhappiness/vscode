
/* Send the OCSP request serialized into BIO 'request' to the
 * responder at given server given by URI.  Returns socket object or
 * NULL on error. */
static apr_socket_t *send_request(BIO *request, const apr_uri_t *uri,
                                  apr_interval_time_t timeout,
                                  conn_rec *c, apr_pool_t *p,
                                  const apr_uri_t *proxy_uri)
{
    apr_status_t rv;
    apr_sockaddr_t *sa;
    apr_socket_t *sd;
    char buf[HUGE_STRING_LEN];
    int len;
    const apr_uri_t *next_hop_uri;

    if (proxy_uri) {
        next_hop_uri = proxy_uri;
    }
    else {
        next_hop_uri = uri;
    }

    rv = apr_sockaddr_info_get(&sa, next_hop_uri->hostname, APR_UNSPEC,
                               next_hop_uri->port, 0, p);
    if (rv) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01972)
                      "could not resolve address of %s %s",
                      proxy_uri ? "proxy" : "OCSP responder",
                      next_hop_uri->hostinfo);
        return NULL;
    }

    /* establish a connection to the OCSP responder */
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(01973)
                  "connecting to %s '%s'",
                  proxy_uri ? "proxy" : "OCSP responder",
                  uri->hostinfo);

    /* Cycle through address until a connect() succeeds. */
    for (; sa; sa = sa->next) {
        rv = apr_socket_create(&sd, sa->family, SOCK_STREAM, APR_PROTO_TCP, p);
        if (rv == APR_SUCCESS) {
            apr_socket_timeout_set(sd, timeout);
