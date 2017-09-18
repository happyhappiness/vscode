	     * APR_POLLHUP first so that a closed connection isn't treated
	     * like an I/O error.  If it is, we never figure out that the
	     * connection is done and we loop here endlessly calling
	     * apr_poll().
	     */
	    if ((rv & APR_POLLIN) || (rv & APR_POLLPRI) || (rv & APR_POLLHUP))
		read_connection(&con[i]);
	    if ((rv & APR_POLLERR) || (rv & APR_POLLNVAL)) {
		bad++;
		err_except++;
		start_connect(&con[i]);
		continue;
	    }
	    if (rv & APR_POLLOUT)
		write_request(&con[i]);

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
	    if (con[i].state == STATE_READ || con[i].state == STATE_CONNECTING)
		apr_poll_socket_add(readbits, con[i].aprsock, APR_POLLIN);

	}
    }

    if (heartbeatres)
	fprintf(stderr, "Finished %ld requests\n", done);
    else
