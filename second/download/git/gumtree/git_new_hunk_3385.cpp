
	va_start(ap, fmt);
	str_len = vsnprintf(NULL, 0, fmt, ap);
	va_end(ap);

	if (str_len < 0) {
		warning_errno("vsnprintf failed");
		return;
	}

	str = malloc(st_add(str_len, 1));
	if (!str) {
		warning_errno("malloc failed");
		return;
	}

	va_start(ap, fmt);
	vsnprintf(str, str_len + 1, fmt, ap);
	va_end(ap);

	while ((pos = strstr(str, "%1")) != NULL) {
		str = realloc(str, st_add(++str_len, 1));
		if (!str) {
			warning_errno("realloc failed");
			return;
		}
		memmove(pos + 2, pos + 1, strlen(pos));
		pos[1] = ' ';
	}

