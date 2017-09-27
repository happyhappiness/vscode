 *        client.
 * FIXME: should allow authentication, but hopefully the
 *        generic proxy authentication is good enough.
 * FIXME: no check for r->assbackwards, whatever that is.
 */

typedef struct {
    apr_array_header_t *allowed_connect_ports;
} connect_conf;

typedef struct {
    int first;
    int last;
} port_range;

static void *create_config(apr_pool_t *p, server_rec *s)
{
    connect_conf *c = apr_pcalloc(p, sizeof(connect_conf));
    c->allowed_connect_ports = apr_array_make(p, 10, sizeof(port_range));
    return c;
}

static void *merge_config(apr_pool_t *p, void *basev, void *overridesv)
{
    connect_conf *c = apr_pcalloc(p, sizeof(connect_conf));
    connect_conf *base = (connect_conf *) basev;
    connect_conf *overrides = (connect_conf *) overridesv;

    c->allowed_connect_ports = apr_array_append(p,
                                                base->allowed_connect_ports,
                                                overrides->allowed_connect_ports);
    
    return c;
}


/*
 * Set the ports CONNECT can use
 */
static const char *
    set_allowed_ports(cmd_parms *parms, void *dummy, const char *arg)
{
    server_rec *s = parms->server;
    int first, last;
    connect_conf *conf =
        ap_get_module_config(s->module_config, &proxy_connect_module);
    port_range *New;
    char *endptr;
    const char *p = arg;

    if (!apr_isdigit(arg[0]))
        return "AllowCONNECT: port numbers must be numeric";

    first = strtol(p, &endptr, 10);
    if (*endptr == '-') {
        p = endptr + 1;
        last = strtol(p, &endptr, 10);
    }
    else {
        last = first;
    }

    if (endptr == p || *endptr != '\0')  {
        return apr_psprintf(parms->temp_pool,
                            "Cannot parse '%s' as port number", p);
    }

    New = apr_array_push(conf->allowed_connect_ports);
    New->first = first;
    New->last  = last;
    return NULL;
}


static int allowed_port(connect_conf *conf, int port)
{
    int i;
    port_range *list = (port_range *) conf->allowed_connect_ports->elts;
    
    if (apr_is_empty_array(conf->allowed_connect_ports)){
        return port == APR_URI_HTTPS_DEFAULT_PORT
               || port == APR_URI_SNEWS_DEFAULT_PORT;
    }

    for (i = 0; i < conf->allowed_connect_ports->nelts; i++) {
        if (port >= list[i].first && port <= list[i].last)
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
    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
                 "proxy: CONNECT: canonicalising URL %s", url);

    return OK;
}

/* read available data (in blocks of CONN_BLKSZ) from c_i and copy to c_o */
static int proxy_connect_transfer(request_rec *r, conn_rec *c_i, conn_rec *c_o,
                                  apr_bucket_brigade *bb, char *name)
{
    int rv;
#ifdef DEBUGGING
    apr_off_t len;
#endif

    do {
        apr_brigade_cleanup(bb);
        rv = ap_get_brigade(c_i->input_filters, bb, AP_MODE_READBYTES,
                            APR_NONBLOCK_READ, CONN_BLKSZ);
        if (rv == APR_SUCCESS) {
            if (c_o->aborted)
                return APR_EPIPE;
            if (APR_BRIGADE_EMPTY(bb))
                break;
#ifdef DEBUGGING
            len = -1;
            apr_brigade_length(bb, 0, &len);
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "proxy: CONNECT: read %" APR_OFF_T_FMT
                          " bytes from %s", len, name);
#endif
            rv = ap_pass_brigade(c_o->output_filters, bb);
            if (rv == APR_SUCCESS) {
                ap_fflush(c_o->output_filters, bb);
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              "proxy: CONNECT: error on %s - ap_pass_brigade",
                              name);
            }
        } else if (!APR_STATUS_IS_EAGAIN(rv)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                          "proxy: CONNECT: error on %s - ap_get_brigade",
                          name);
        }
    } while (rv == APR_SUCCESS);

    if (APR_STATUS_IS_EAGAIN(rv)) {
        rv = APR_SUCCESS;
    }
    return rv;
}

/* CONNECT handler */
static int proxy_connect_handler(request_rec *r, proxy_worker *worker,
                                 proxy_server_conf *conf,
                                 char *url, const char *proxyname,
                                 apr_port_t proxyport)
{
    connect_conf *c_conf =
        ap_get_module_config(r->server->module_config, &proxy_connect_module);

    apr_pool_t *p = r->pool;
    apr_socket_t *sock;
    conn_rec *c = r->connection;
    conn_rec *backconn;

    apr_bucket_brigade *bb = apr_brigade_create(p, c->bucket_alloc);
    apr_status_t err, rv;
    apr_size_t nbytes;
    char buffer[HUGE_STRING_LEN];
    apr_socket_t *client_socket = ap_get_module_config(c->conn_config, &core_module);
    int failed, rc;
    int client_error = 0;
    apr_pollset_t *pollset;
    apr_pollfd_t pollfd;
    const apr_pollfd_t *signalled;
    apr_int32_t pollcnt, pi;
    apr_int16_t pollevent;
    apr_sockaddr_t *uri_addr, *connect_addr;
