            e = APR_SUCCESS;
        }
        else
#endif
            e = apr_socket_send(c->aprsock, request + c->rwrote, &l);

        if (e != APR_SUCCESS && !APR_STATUS_IS_EAGAIN(e)) {
            epipe++;
            printf("Send request failed!\n");
            close_connection(c);
            return;
        }
        totalposted += l;
        c->rwrote += l;
        c->rwrite -= l;
    } while (c->rwrite);

    c->state = STATE_READ;
    c->endwrite = lasttime = apr_time_now();
    {
        apr_pollfd_t new_pollfd;
        new_pollfd.desc_type = APR_POLL_SOCKET;
        new_pollfd.reqevents = APR_POLLIN;
        new_pollfd.desc.s = c->aprsock;
        new_pollfd.client_data = c;
