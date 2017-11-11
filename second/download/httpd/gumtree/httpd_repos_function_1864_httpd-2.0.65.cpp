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