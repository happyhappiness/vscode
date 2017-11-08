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