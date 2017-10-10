				/* Split <host>:<port> at colon. */
				char *host;
				char *port;
				parse_host_and_port(val, &host, &port);
				if (port) {
					free(tcp_port);
					tcp_port = sanitize_client(port);
				}
				free(hostname);
				hostname = canonicalize_client(host);
				hostname_lookup_done = 0;
			}

			/* On to the next one */
			extra_args = val + vallen;
		}
		if (extra_args < end && *extra_args)
			die("Invalid request");
	}
}

/*
 * Locate canonical hostname and its IP address.
 */
static void lookup_hostname(void)
{
	if (!hostname_lookup_done && hostname) {
#ifndef NO_IPV6
		struct addrinfo hints;
		struct addrinfo *ai;
		int gai;
		static char addrbuf[HOST_NAME_MAX + 1];

