                             proxy_function,
                             backend_addr,
                             worker->s->hostname);
                backend_addr = backend_addr->next;
                continue;
            }
        }

        /* Set a timeout on the socket */
        if (worker->s->timeout_set) {
            apr_socket_timeout_set(newsock, worker->s->timeout);
        }
