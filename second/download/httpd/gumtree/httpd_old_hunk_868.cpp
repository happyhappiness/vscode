     * So set reuseaddr, but do not attempt to do so until we have the
     * parent listeners successfully bound.
     */
    stat = apr_socket_opt_set(s, APR_SO_REUSEADDR, one);
    if (stat != APR_SUCCESS && stat != APR_ENOTIMPL) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, stat, p,
                    "make_sock: for address %pI, apr_socket_opt_set: (SO_REUSEADDR)", 
                     server->bind_addr);
        apr_socket_close(s);
        return stat;
    }
#endif

#if APR_HAS_SO_ACCEPTFILTER
#ifndef ACCEPT_FILTER_NAME
#define ACCEPT_FILTER_NAME "httpready"
#ifdef __FreeBSD_version
#if __FreeBSD_version < 411000 /* httpready was broken before 4.1.1 */
#undef ACCEPT_FILTER_NAME
#define ACCEPT_FILTER_NAME "dataready"
#endif
#endif
#endif
    apr_socket_accept_filter(s, ACCEPT_FILTER_NAME, "");
#endif

    server->sd = s;
    server->active = 1;

#ifdef MPM_ACCEPT_FUNC
    server->accept_func = MPM_ACCEPT_FUNC;
#else
    server->accept_func = NULL;
#endif

    return APR_SUCCESS;
}

static apr_status_t close_listeners_on_exec(void *v)
{
    ap_listen_rec *lr;

    for (lr = ap_listeners; lr; lr = lr->next) {
        apr_socket_close(lr->sd);
        lr->active = 0;
    }

    return APR_SUCCESS;
}


static void find_default_family(apr_pool_t *p)
{
#if APR_HAVE_IPV6
    /* We know the platform supports IPv6, but this particular
     * system may not have IPv6 enabled.  See if we can get an
     * AF_INET6 socket and bind to an ephemeral port.  (On most
     * systems, getting an AF_INET6 socket is a sufficient test.
     * On certain levels of OpenUNIX, getting the socket is
     * successful but bind always returns ENETUNREACH.)
     */
    if (default_family == APR_UNSPEC) {
        apr_status_t sock_rv;
        apr_socket_t *tmp_sock;
        apr_sockaddr_t *sa;

        if ((sock_rv = apr_socket_create(&tmp_sock, APR_INET6, SOCK_STREAM, p)) 
            == APR_SUCCESS &&
            apr_sockaddr_info_get(&sa, NULL, APR_INET6, 0, 0, p) == APR_SUCCESS &&
            apr_bind(tmp_sock, sa) == APR_SUCCESS) { 
            default_family = APR_INET6;
        }
        else {
            default_family = APR_INET;
        }
        if (sock_rv == APR_SUCCESS) {
            apr_socket_close(tmp_sock);
        }
    }
#endif
}


static const char *alloc_listener(process_rec *process, char *addr, apr_port_t port)
{
    ap_listen_rec **walk;
    ap_listen_rec *new;
    apr_status_t status;
    apr_port_t oldport;
    apr_sockaddr_t *sa;

    if (!addr) { /* don't bind to specific interface */
        find_default_family(process->pool);
        switch(default_family) {
        case APR_INET:
            addr = "0.0.0.0";
            break;

#if APR_HAVE_IPV6
        case APR_INET6:
            addr = "::";
            break;
#endif

        default:
            ap_assert(1 != 1); /* should not occur */
        }
    }

    /* see if we've got an old listener for this address:port */
    for (walk = &old_listeners; *walk; walk = &(*walk)->next) {
        sa = (*walk)->bind_addr;
        /* Some listeners are not real so they will not have a bind_addr. */
        if (sa) {
            apr_sockaddr_port_get(&oldport, sa);
            if (!strcmp(sa->hostname, addr) && port == oldport) {
                /* re-use existing record */
                new = *walk;
                *walk = new->next;
                new->next = ap_listeners;
                ap_listeners = new;
                return NULL;
            }
        }
    }

    /* this has to survive restarts */
    new = apr_palloc(process->pool, sizeof(ap_listen_rec));
    new->active = 0;
    if ((status = apr_sockaddr_info_get(&new->bind_addr, addr, APR_UNSPEC,
                                        port, 0, process->pool))
        != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, status, process->pool,
                      "alloc_listener: failed to set up sockaddr for %s",
                      addr);
        return "Listen setup failed";
    }
    if ((status = apr_socket_create(&new->sd,
                                    new->bind_addr->family,
                                    SOCK_STREAM, process->pool))
        != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, status, process->pool,
                      "alloc_listener: failed to get a socket for %s", addr);
        return "Listen setup failed";
    }

    new->next = ap_listeners;
    ap_listeners = new;
    return NULL;
}

static int ap_listen_open(apr_pool_t *pool, apr_port_t port)
{
    ap_listen_rec *lr;
    ap_listen_rec *next;
    int num_open;
    const char *userdata_key = "ap_listen_open";
    void *data;

    /* Don't allocate a default listener.  If we need to listen to a
     * port, then the user needs to have a Listen directive in their
     * config file.
     */
    num_open = 0;
    for (lr = ap_listeners; lr; lr = lr->next) {
        if (lr->active) {
            ++num_open;
        }
        else {
            if (make_sock(pool, lr) == APR_SUCCESS) {
                ++num_open;
                lr->active = 1;
            }
            else {
                /* fatal error */
                return -1;
            }
        }
    }

