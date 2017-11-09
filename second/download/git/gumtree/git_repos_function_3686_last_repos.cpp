static void parse_host_arg(struct hostinfo *hi, char *extra_args, int buflen)
{
	char *val;
	int vallen;
	char *end = extra_args + buflen;

	if (extra_args < end && *extra_args) {
		hi->saw_extended_args = 1;
		if (strncasecmp("host=", extra_args, 5) == 0) {
			val = extra_args + 5;
			vallen = strlen(val) + 1;
			if (*val) {
				/* Split <host>:<port> at colon. */
				char *host;
				char *port;
				parse_host_and_port(val, &host, &port);
				if (port)
					sanitize_client(&hi->tcp_port, port);
				canonicalize_client(&hi->hostname, host);
				hi->hostname_lookup_done = 0;
			}

			/* On to the next one */
			extra_args = val + vallen;
		}
		if (extra_args < end && *extra_args)
			die("Invalid request");
	}
}