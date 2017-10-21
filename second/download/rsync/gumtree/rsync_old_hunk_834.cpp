		}
#endif

		/* Now we've got a socket - we need to bind it. */
		if (bind(s, resp->ai_addr, resp->ai_addrlen) < 0) {
			/* Nope, try another */
			close(s);
			continue;
		}

		socks[i++] = s;
	}
	socks[i] = -1;

	if (all_ai)
		freeaddrinfo(all_ai);

	if (!i) {
		rprintf(FERROR,
			"unable to bind any inbound sockets on port %d\n",
			port);
		free(socks);
		return NULL;
