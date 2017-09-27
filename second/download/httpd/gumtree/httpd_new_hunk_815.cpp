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

    server->sd = s;
    server->active = 1;

#ifdef MPM_ACCEPT_FUNC
    server->accept_func = MPM_ACCEPT_FUNC;
#else
    server->accept_func = NULL;
#endif

    return APR_SUCCESS;
}

static const char* find_accf_name(server_rec *s, const char *proto)
{
    const char* accf;
    core_server_config *conf = ap_get_module_config(s->module_config,
                                                    &core_module);
    if (!proto) {
        return NULL;
    }

    accf = apr_table_get(conf->accf_map, proto);

    if (accf && !strcmp("none", accf)) {
        return NULL;
    }

    return accf;
}

static void ap_apply_accept_filter(apr_pool_t *p, ap_listen_rec *lis,
                                           server_rec *server)
{
    apr_socket_t *s = lis->sd;
    const char *accf;
    apr_status_t rv;
    const char *proto;

    proto = lis->protocol;

    if (!proto) {
        proto = ap_get_server_protocol(server);
    }


    accf = find_accf_name(server, proto);

    if (accf) {
#if APR_HAS_SO_ACCEPTFILTER
        rv = apr_socket_accept_filter(s, apr_pstrdup(p, accf),
                                      apr_pstrdup(p,""));
        if (rv != APR_SUCCESS && !APR_STATUS_IS_ENOTIMPL(rv)) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, rv, p,
                          "Failed to enable the '%s' Accept Filter",
                          accf);
        }
#else
#ifdef APR_TCP_DEFER_ACCEPT
        rv = apr_socket_opt_set(s, APR_TCP_DEFER_ACCEPT, 1);
        if (rv != APR_SUCCESS && !APR_STATUS_IS_ENOTIMPL(rv)) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, rv, p,
                              "Failed to enable APR_TCP_DEFER_ACCEPT");
        }
#endif
#endif
    }
}

static apr_status_t close_listeners_on_exec(void *v)
{
    ap_close_listeners();
    return APR_SUCCESS;
}

static const char *alloc_listener(process_rec *process, char *addr,
                                  apr_port_t port, const char* proto)
{
    ap_listen_rec **walk, *last;
    apr_status_t status;
    apr_sockaddr_t *sa;
    int found_listener = 0;

    /* see if we've got an old listener for this address:port */
    for (walk = &old_listeners; *walk;) {
        sa = (*walk)->bind_addr;
        /* Some listeners are not real so they will not have a bind_addr. */
        if (sa) {
            ap_listen_rec *new;
            apr_port_t oldport;

            oldport = sa->port;
            /* If both ports are equivalent, then if their names are equivalent,
             * then we will re-use the existing record.
             */
            if (port == oldport &&
                ((!addr && !sa->hostname) ||
                 ((addr && sa->hostname) && !strcmp(sa->hostname, addr)))) {
                new = *walk;
                *walk = new->next;
                new->next = ap_listeners;
                ap_listeners = new;
                found_listener = 1;
                continue;
            }
        }

        walk = &(*walk)->next;
    }

    if (found_listener) {
        return NULL;
    }

    if ((status = apr_sockaddr_info_get(&sa, addr, APR_UNSPEC, port, 0,
                                        process->pool))
        != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, status, process->pool,
                      "alloc_listener: failed to set up sockaddr for %s",
                      addr);
        return "Listen setup failed";
    }

    /* Initialize to our last configured ap_listener. */
    last = ap_listeners;
    while (last && last->next) {
        last = last->next;
    }

    while (sa) {
        ap_listen_rec *new;

        /* this has to survive restarts */
        new = apr_palloc(process->pool, sizeof(ap_listen_rec));
        new->active = 0;
        new->next = 0;
        new->bind_addr = sa;
        new->protocol = apr_pstrdup(process->pool, proto);

        /* Go to the next sockaddr. */
        sa = sa->next;

        status = apr_socket_create(&new->sd, new->bind_addr->family,
                                    SOCK_STREAM, 0, process->pool);

#if APR_HAVE_IPV6
        /* What could happen is that we got an IPv6 address, but this system
         * doesn't actually support IPv6.  Try the next address.
         */
        if (status != APR_SUCCESS && !addr &&
            new->bind_addr->family == APR_INET6) {
            continue;
        }
#endif
        if (status != APR_SUCCESS) {
            ap_log_perror(APLOG_MARK, APLOG_CRIT, status, process->pool,
                          "alloc_listener: failed to get a socket for %s",
                          addr);
            return "Listen setup failed";
        }

        /* We need to preserve the order returned by getaddrinfo() */
        if (last == NULL) {
            ap_listeners = last = new;
        } else {
            last->next = new;
            last = new;
        }
    }

    return NULL;
}
/* Evaluates to true if the (apr_sockaddr_t *) addr argument is the
 * IPv4 match-any-address, 0.0.0.0. */
#define IS_INADDR_ANY(addr) ((addr)->family == APR_INET \
                             && (addr)->sa.sin.sin_addr.s_addr == INADDR_ANY)

/* Evaluates to true if the (apr_sockaddr_t *) addr argument is the
 * IPv6 match-any-address, [::]. */
#define IS_IN6ADDR_ANY(addr) ((addr)->family == APR_INET6 \
                              && IN6_IS_ADDR_UNSPECIFIED(&(addr)->sa.sin6.sin6_addr))

/**
 * Create, open, listen, and bind all sockets.
 * @param process The process record for the currently running server
 * @return The number of open sockets
 */
static int open_listeners(apr_pool_t *pool)
{
    ap_listen_rec *lr;
    ap_listen_rec *next;
    ap_listen_rec *previous;
    int num_open;
    const char *userdata_key = "ap_open_listeners";
    void *data;

    /* Don't allocate a default listener.  If we need to listen to a
     * port, then the user needs to have a Listen directive in their
     * config file.
     */
    num_open = 0;
    previous = NULL;
    for (lr = ap_listeners; lr; previous = lr, lr = lr->next) {
        if (lr->active) {
            ++num_open;
        }
        else {
#if APR_HAVE_IPV6
            int v6only_setting;

            /* If we have the unspecified IPv4 address (0.0.0.0) and
             * the unspecified IPv6 address (::) is next, we need to
             * swap the order of these in the list. We always try to
             * bind to IPv6 first, then IPv4, since an IPv6 socket
             * might be able to receive IPv4 packets if V6ONLY is not
             * enabled, but never the other way around. */
            if (lr->next != NULL
                && IS_INADDR_ANY(lr->bind_addr)
                && lr->bind_addr->port == lr->next->bind_addr->port
                && IS_IN6ADDR_ANY(lr->next->bind_addr)) {
                /* Exchange lr and lr->next */
                next = lr->next;
                lr->next = next->next;
                next->next = lr;
                if (previous) {
                    previous->next = next;
                }
                else {
                    ap_listeners = next;
                }
                lr = next;
            }

            /* If we are trying to bind to 0.0.0.0 and the previous listener
             * was :: on the same port and in turn that socket does not have
             * the IPV6_V6ONLY flag set; we must skip the current attempt to
             * listen (which would generate an error). IPv4 will be handled
             * on the established IPv6 socket.
             */
            if (previous != NULL
                && IS_INADDR_ANY(lr->bind_addr)
                && lr->bind_addr->port == previous->bind_addr->port
                && IS_IN6ADDR_ANY(previous->bind_addr)
                && apr_socket_opt_get(previous->sd, APR_IPV6_V6ONLY,
                                      &v6only_setting) == APR_SUCCESS
                && v6only_setting == 0) {

                /* Remove the current listener from the list */
                previous->next = lr->next;
                continue;
            }
#endif
            if (make_sock(pool, lr) == APR_SUCCESS) {
                ++num_open;
                lr->active = 1;
            }
            else {
#if APR_HAVE_IPV6
                /* If we tried to bind to ::, and the next listener is
                 * on 0.0.0.0 with the same port, don't give a fatal
                 * error. The user will still get a warning from make_sock
                 * though.
                 */
                if (lr->next != NULL
                    && IS_IN6ADDR_ANY(lr->bind_addr)
                    && lr->bind_addr->port == lr->next->bind_addr->port
                    && IS_INADDR_ANY(lr->next->bind_addr)) {

                    /* Remove the current listener from the list */
                    if (previous) {
                        previous->next = lr->next;
                    }
                    else {
                        ap_listeners = lr->next;
                    }

                    /* Although we've removed ourselves from the list,
                     * we need to make sure that the next iteration won't
                     * consider "previous" a working IPv6 '::' socket.
                     * Changing the family is enough to make sure the
                     * conditions before make_sock() fail.
                     */
                    lr->bind_addr->family = AF_INET;

                    continue;
                }
#endif
                /* fatal error */
                return -1;
            }
        }
    }

