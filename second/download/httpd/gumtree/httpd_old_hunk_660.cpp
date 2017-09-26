    }

    return OK;
}

static int nwssl_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                             apr_pool_t *ptemp, server_rec *s)
{
    seclisten_rec* sl;
    ap_listen_rec* lr;
    apr_socket_t*  sd;
    apr_status_t status;
    seclistenup_rec *slu;
    int found;

    for (sl = ap_seclisteners; sl != NULL; sl = sl->next) {
        sl->fd = find_secure_listener(sl);

        if (sl->fd < 0)
            sl->fd = make_secure_socket(pconf, &sl->local_addr,
                                        sl->key, sl->mutual, s);

        if (sl->fd >= 0) {
            apr_os_sock_info_t sock_info;

            sock_info.os_sock = &(sl->fd);
            sock_info.local = (struct sockaddr*)&(sl->local_addr);
            sock_info.remote = NULL;
            sock_info.family = APR_INET;
            sock_info.type = SOCK_STREAM;

            apr_os_sock_make(&sd, &sock_info, pconf);

            lr = apr_pcalloc(pconf, sizeof(ap_listen_rec));

            if (lr) {
                lr->sd = sd;
                if ((status = apr_sockaddr_info_get(&lr->bind_addr, sl->addr,
                        APR_UNSPEC, sl->port, 0, pconf)) != APR_SUCCESS) {
                    ap_log_perror(APLOG_MARK, APLOG_CRIT, status, pconf,
                                  "alloc_listener: failed to set up sockaddr for %s:%d",
                                  sl->addr, sl->port);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
                lr->next = ap_listeners;
                ap_listeners = lr;
                apr_pool_cleanup_register(pconf, lr, nwssl_socket_cleanup, apr_pool_cleanup_null);
            }
        } else {
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

