
	if (str_len < 0) {
		warning("vsnprintf failed: '%s'", strerror(errno));
		return;
	}

	str = malloc(st_add(str_len, 1));
	if (!str) {
		warning("malloc failed: '%s'", strerror(errno));
		return;
	}

	va_start(ap, fmt);
	vsnprintf(str, str_len + 1, fmt, ap);
	va_end(ap);

	while ((pos = strstr(str, "%1")) != NULL) {
		str = realloc(str, st_add(++str_len, 1));
		if (!str) {
			warning("realloc failed: '%s'", strerror(errno));
			return;
		}
		memmove(pos + 2, pos + 1, strlen(pos));
		pos[1] = ' ';
