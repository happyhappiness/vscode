             * call read_connection() for APR_POLLHUP, so check for
             * APR_POLLHUP first so that a closed connection isn't treated
             * like an I/O error.  If it is, we never figure out that the
             * connection is done and we loop here endlessly calling
             * apr_poll().
             */
            if ((rtnev & APR_POLLIN) || (rtnev & APR_POLLPRI) || (rtnev & APR_POLLHUP))
                read_connection(c);
            if ((rtnev & APR_POLLERR) || (rtnev & APR_POLLNVAL)) {
                bad++;
                err_except++;
                /* avoid apr_poll/EINPROGRESS loop on HP-UX, let recv discover ECONNREFUSED */
                if (c->state == STATE_CONNECTING) { 
                    read_connection(c);
                }
                else { 
                    start_connect(c);
                }
                continue;
            }
            if (rtnev & APR_POLLOUT) {
                if (c->state == STATE_CONNECTING) {
                    rv = apr_socket_connect(c->aprsock, destsa);
                    if (rv != APR_SUCCESS) {
                        set_conn_state(c, STATE_UNCONNECTED);
                        apr_socket_close(c->aprsock);
                        err_conn++;
                        if (bad++ > 10) {
                            fprintf(stderr,
                                    "\nTest aborted after 10 failures\n\n");
                            apr_err("apr_socket_connect()", rv);
                        }
                        start_connect(c);
                        continue;
                    }
                    else {
                        set_conn_state(c, STATE_CONNECTED);
#ifdef USE_SSL
                        if (c->ssl)
                            ssl_proceed_handshake(c);
                        else
#endif
                        write_request(c);
                    }
                }
                else {
                    write_request(c);
                }
            }
        }
    } while (lasttime < stoptime && done < requests);
    
    if (heartbeatres)
        fprintf(stderr, "Finished %d requests\n", done);
    else
