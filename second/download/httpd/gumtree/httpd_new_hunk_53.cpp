	     * APR_POLLHUP first so that a closed connection isn't treated
	     * like an I/O error.  If it is, we never figure out that the
	     * connection is done and we loop here endlessly calling
	     * apr_poll().
	     */
	    if ((rv & APR_POLLIN) || (rv & APR_POLLPRI) || (rv & APR_POLLHUP))
		read_connection(c);
	    if ((rv & APR_POLLERR) || (rv & APR_POLLNVAL)) {
		bad++;
		err_except++;
		start_connect(c);
		continue;
	    }
	    if (rv & APR_POLLOUT)
		write_request(c);

	    /*
	     * When using a select based poll every time we check the bits
	     * are reset. In 1.3's ab we copied the FD_SET's each time
	     * through, but here we're going to check the state and if the
	     * connection is in STATE_READ or STATE_CONNECTING we'll add the
	     * socket back in as APR_POLLIN.
	     */
#ifdef USE_SSL
            if (ssl != 1)
#endif
	    if (c->state == STATE_READ ||
                c->state == STATE_CONNECTING) {
                    apr_pollfd_t new_pollfd;
                    new_pollfd.desc_type = APR_POLL_SOCKET;
                    new_pollfd.reqevents = APR_POLLIN;
                    new_pollfd.desc.s = c->aprsock;
                    new_pollfd.client_data = c;
                    apr_pollset_add(readbits, &new_pollfd);
                }
	}
    }

    if (heartbeatres)
	fprintf(stderr, "Finished %ld requests\n", done);
    else
