            apr_socket_timeout_set(newsock, conf->timeout);
        }
        else {
             apr_socket_timeout_set(newsock, s->timeout);
        }

        conn->sock   = newsock;
        connected    = 1;
    }
    /*
     * Put the entire worker to error state if
     * the PROXY_WORKER_IGNORE_ERRORS flag is not set.
     * Altrough some connections may be alive
