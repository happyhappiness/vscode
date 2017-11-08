char *gitdirname(char *path)
{
	static struct strbuf buf = STRBUF_INIT;
	char *p = path, *slash = NULL, c;
	int dos_drive_prefix;

	if (!p)
		return ".";

	if ((dos_drive_prefix = skip_dos_drive_prefix(&p)) && !*p)
		goto dot;

	/*
	 * POSIX.1-2001 says dirname("/") should return "/", and dirname("//")
	 * should return "//", but dirname("///") should return "/" again.
	 */
	if (is_dir_sep(*p)) {
		if (!p[1] || (is_dir_sep(p[1]) && !p[2]))
			return path;
		slash = ++p;
	}
	while ((c = *(p++)))
		if (is_dir_sep(c)) {
			char *tentative = p - 1;

			/* POSIX.1-2001 says to ignore trailing slashes */
			while (is_dir_sep(*p))
				p++;
			if (*p)
				slash = tentative;
		}

	if (slash) {
		*slash = '\0';
		return path;
	}

dot:
	strbuf_reset(&buf);
	strbuf_addf(&buf, "%.*s.", dos_drive_prefix, path);
	return buf.buf;
}