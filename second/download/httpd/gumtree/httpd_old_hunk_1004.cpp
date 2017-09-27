		fprintf(stderr, "Completed %ld requests\n", done);
		fflush(stderr);
	    }
	    c->done = apr_time_now();
	    s.read = c->read;
	    s.starttime = c->start;
	    s.ctime = (c->connect - c->start) / 1000;
	    s.time = (c->done - c->start) / 1000;
	    s.waittime = (c->beginread - c->endwrite) / 1000;
	    stats[done++] = s;
	}
    }

#ifdef USE_SSL
    if (ssl == 1) {
        SSL_shutdown(c->ssl);
        SSL_free(c->ssl);
    }
    else
#endif
    {
        apr_pollfd_t remove_pollfd;
        remove_pollfd.desc_type = APR_POLL_SOCKET;
        remove_pollfd.desc.s = c->aprsock;
        apr_pollset_remove(readbits, &remove_pollfd);
        apr_socket_close(c->aprsock);
    }
    c->state = STATE_UNCONNECTED;

    /* connect again */
    start_connect(c);
