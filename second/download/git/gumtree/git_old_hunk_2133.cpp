		die("cannot start proxy %s", git_proxy_command);
	fd[0] = proxy->out; /* read from proxy stdout */
	fd[1] = proxy->in;  /* write to proxy stdin */
	return proxy;
}

static const char *get_port_numeric(const char *p)
{
	char *end;
	if (p) {
		long port = strtol(p + 1, &end, 10);
		if (end != p + 1 && *end == '\0' && 0 <= port && port < 65536) {
			return p;
		}
	}

	return NULL;
}

