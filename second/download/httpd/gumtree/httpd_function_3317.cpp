static int nwssl_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                          apr_pool_t *ptemp, server_rec *s)
{
    seclisten_rec* sl;
    ap_listen_rec* lr;
    apr_socket_t*  sd;
    apr_status_t status;
    seclistenup_rec *slu;
    int found;
    ap_listen_rec *walk;
    seclisten_rec *secwalk, *lastsecwalk;
    apr_sockaddr_t *sa;

    /* Walk the old listeners list and compare it to the secure
       listeners list and remove any secure listener records that
       are not being reused */
    for (walk = nw_old_listeners; walk; walk = walk->next) {
        sa = walk->bind_addr;
        if (sa) {
            ap_listen_rec *new;
            apr_port_t oldport;

            oldport = sa->port;
            for (secwalk = ap_seclisteners, lastsecwalk = ap_seclisteners; secwalk; secwalk = lastsecwalk->next) {
                unsigned short port = secwalk->port;
                char *addr = secwalk->addr;
                /* If both ports are equivalent, then if their names are equivalent,
                 * then we will re-use the existing record.
                 */
                if (port == oldport &&
                    ((!addr && !sa->hostname) ||
                     ((addr && sa->hostname) && !strcmp(sa->hostname, addr)))) {
                    if (secwalk == ap_seclisteners) {
                        ap_seclisteners = secwalk->next;
                    }
                    else {
                        lastsecwalk->next = secwalk->next;
                    }
                    apr_socket_close(walk->sd);
                    walk->active = 0;
                    break;
                }
                else {
                    lastsecwalk = secwalk;
                }
            }
        }
    }

    for (sl = ap_seclisteners; sl != NULL; sl = sl->next) {
        /* If we find a pre-existing listen socket and it has already been
           created, then no neeed to go any further, just reuse it. */
        if (((sl->fd = find_secure_listener(sl)) >= 0) && (sl->used)) {
            continue;
        }

        if (sl->fd < 0)
            sl->fd = make_secure_socket(s->process->pool, &sl->local_addr, sl->key, sl->mutual, s);

        if (sl->fd >= 0) {
            apr_os_sock_info_t sock_info;

            sock_info.os_sock = &(sl->fd);
            sock_info.local = (struct sockaddr*)&(sl->local_addr);
            sock_info.remote = NULL;
            sock_info.family = APR_INET;
            sock_info.type = SOCK_STREAM;

            apr_os_sock_make(&sd, &sock_info, s->process->pool);

            lr = apr_pcalloc(s->process->pool, sizeof(ap_listen_rec));

            if (lr) {
                lr->sd = sd;
                if ((status = apr_sockaddr_info_get(&lr->bind_addr, sl->addr, APR_UNSPEC, sl->port, 0,
                                              s->process->pool)) != APR_SUCCESS) {
                    ap_log_perror(APLOG_MARK, APLOG_CRIT, status, pconf,
                                 "alloc_listener: failed to set up sockaddr for %s:%d", sl->addr, sl->port);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
                lr->next = ap_listeners;
                ap_listeners = lr;
                apr_pool_cleanup_register(s->process->pool, lr, nwssl_socket_cleanup, apr_pool_cleanup_null);
            }
        } else {
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    for (slu = ap_seclistenersup; slu; slu = slu->next) {
        /* Check the listener list for a matching upgradeable listener */
        found = 0;
        for (lr = ap_listeners; lr; lr = lr->next) {
            if (slu->port == lr->bind_addr->port) {
                found = 1;
                break;
            }
        }
        if (!found) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, plog,
                         "No Listen directive found for upgradeable listener %s:%d", slu->addr, slu->port);
        }
    }

    build_cert_list(s->process->pool);

    return OK;
}