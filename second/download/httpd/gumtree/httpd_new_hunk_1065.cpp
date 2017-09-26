		start_connect(c);
		continue;
	    }
	    if (rv & APR_POLLOUT) {
                if (c->state == STATE_CONNECTING) {
                    apr_pollfd_t remove_pollfd;
                    rv = apr_socket_connect(c->aprsock, destsa);
                    remove_pollfd.desc_type = APR_POLL_SOCKET;
                    remove_pollfd.desc.s = c->aprsock;
                    apr_pollset_remove(readbits, &remove_pollfd);
                    if (rv != APR_SUCCESS) {
                        apr_socket_close(c->aprsock);
                        err_conn++;
                        if (bad++ > 10) {
                            fprintf(stderr,
                                    "\nTest aborted after 10 failures\n\n");
                            apr_err("apr_socket_connect()", rv);
                        }
                        c->state = STATE_UNCONNECTED;
                        start_connect(c);
                        continue;
                    }
                    else {
                        c->state = STATE_CONNECTED;
                        started++;
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
