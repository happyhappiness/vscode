            remove_pollfd.desc.s = c->aprsock;
	    apr_pollset_remove(readbits, &remove_pollfd);
	    apr_socket_close(c->aprsock);
	    err_conn++;
	    if (bad++ > 10) {
		fprintf(stderr,
			"\nTest aborted after 10 failures\n\n");
		apr_err("apr_connect()", rv);
	    }
	    c->state = STATE_UNCONNECTED;
	    start_connect(c);
	    return;
	}
    }

    /* connected first time */
    c->state = STATE_CONNECTED;
    started++;
    write_request(c);
}

/* --------------------------------------------------------- */

/* close down connection and save stats */

