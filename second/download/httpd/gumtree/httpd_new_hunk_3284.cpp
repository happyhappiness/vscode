        if (status != APR_SUCCESS && !addr &&
            new->bind_addr->family == APR_INET6) {
            continue;
        }
#endif
        if (status != APR_SUCCESS) {
            ap_log_perror(APLOG_MARK, APLOG_CRIT, status, process->pool, APLOGNO(00078)
                          "alloc_listener: failed to get a socket for %s",
                          addr);
            return "Listen setup failed";
        }

        /* We need to preserve the order returned by getaddrinfo() */
