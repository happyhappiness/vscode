 *        client.
 * FIXME: should allow authentication, but hopefully the
 *        generic proxy authentication is good enough.
 * FIXME: no check for r->assbackwards, whatever that is.
 */

static int allowed_port(proxy_server_conf *conf, int port)
{
    int i;
    int *list = (int *) conf->allowed_connect_ports->elts;

    for(i = 0; i < conf->allowed_connect_ports->nelts; i++) {
    if(port == list[i])
        return 1;
    }
    return 0;
}

/* canonicalise CONNECT URLs. */
static int proxy_connect_canon(request_rec *r, char *url)
{

    if (r->method_number != M_CONNECT) {
    return DECLINED;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
         "proxy: CONNECT: canonicalising URL %s", url);

    return OK;
}

/* CONNECT handler */
static int proxy_connect_handler(request_rec *r, proxy_worker *worker,
                                 proxy_server_conf *conf,
                                 char *url, const char *proxyname,
                                 apr_port_t proxyport)
{
    apr_pool_t *p = r->pool;
    apr_socket_t *sock;
    apr_status_t err, rv;
    apr_size_t i, o, nbytes;
    char buffer[HUGE_STRING_LEN];
    apr_socket_t *client_socket = ap_get_module_config(r->connection->conn_config, &core_module);
    int failed;
    apr_pollset_t *pollset;
    apr_pollfd_t pollfd;
    const apr_pollfd_t *signalled;
    apr_int32_t pollcnt, pi;
    apr_int16_t pollevent;
    apr_sockaddr_t *uri_addr, *connect_addr;
