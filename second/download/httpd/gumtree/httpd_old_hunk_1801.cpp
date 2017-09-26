            e = APR_SUCCESS;
        }
        else
#endif
            e = apr_socket_send(c->aprsock, request + c->rwrote, &l);

        /*
         * Bail early on the most common case
         */
        if (l == c->rwrite)
            break;

        if (e != APR_SUCCESS) {
            /*
             * Let's hope this traps EWOULDBLOCK too !
             */
            if (!APR_STATUS_IS_EAGAIN(e)) {
                epipe++;
                printf("Send request failed!\n");
                close_connection(c);
            }
            return;
        }
        c->rwrote += l;
        c->rwrite -= l;
    } while (1);

    totalposted += c->rwrite;
    c->state = STATE_READ;
    c->endwrite = apr_time_now();
    {
        apr_pollfd_t new_pollfd;
        new_pollfd.desc_type = APR_POLL_SOCKET;
        new_pollfd.reqevents = APR_POLLIN;
        new_pollfd.desc.s = c->aprsock;
        new_pollfd.client_data = c;
