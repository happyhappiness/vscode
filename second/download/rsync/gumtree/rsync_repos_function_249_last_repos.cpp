int open_socket_out_wrapped(char *host, int port, const char *bind_addr,
			    int af_hint)
{
	char *prog = getenv("RSYNC_CONNECT_PROG");

	if (prog && strchr(prog, '%')) {
		int hlen = strlen(host);
		int len = strlen(prog) + 1;
		char *f, *t;
		for (f = prog; *f; f++) {
			if (*f != '%')
				continue;
			/* Compute more than enough room. */
			if (f[1] == '%')
				f++;
			else
				len += hlen;
		}
		f = prog;
		if (!(prog = new_array(char, len)))
			out_of_memory("open_socket_out_wrapped");
		for (t = prog; *f; f++) {
			if (*f == '%') {
				switch (*++f) {
				case '%':
					/* Just skips the extra '%'. */
					break;
				case 'H':
					memcpy(t, host, hlen);
					t += hlen;
					continue;
				default:
					f--; /* pass % through */
					break;
				}
			}
			*t++ = *f;
		}
		*t = '\0';
	}

	if (DEBUG_GTE(CONNECT, 1)) {
		rprintf(FINFO, "%sopening tcp connection to %s port %d\n",
			prog ? "Using RSYNC_CONNECT_PROG instead of " : "",
			host, port);
	}
	if (prog)
		return sock_exec(prog);
	return open_socket_out(host, port, bind_addr, af_hint);
}