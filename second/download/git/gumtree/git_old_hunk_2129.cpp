				/* Split <host>:<port> at colon. */
				char *host;
				char *port;
				parse_host_and_port(val, &host, &port);
				if (port) {
					free(tcp_port);
					tcp_port = xstrdup(port);
				}
				free(hostname);
				hostname = xstrdup_tolower(host);
			}

			/* On to the next one */
			extra_args = val + vallen;
		}
		if (extra_args < end && *extra_args)
			die("Invalid request");
	}

	/*
	 * Locate canonical hostname and its IP address.
	 */
	if (hostname) {
#ifndef NO_IPV6
		struct addrinfo hints;
		struct addrinfo *ai;
		int gai;
		static char addrbuf[HOST_NAME_MAX + 1];

