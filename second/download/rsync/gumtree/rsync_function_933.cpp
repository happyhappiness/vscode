static char *expand_vars(char *str)
{
	char *buf, *t, *f;
	int bufsize;

	if (strchr(str, '%') == NULL)
		return str;

	bufsize = strlen(str) + 2048;
	if ((buf = new_array(char, bufsize+1)) == NULL) /* +1 for trailing '\0' */
		out_of_memory("expand_vars");

	for (t = buf, f = str; bufsize && *f; ) {
		if (*f == '%' && *++f != '%') {
			char *percent = strchr(f, '%');
			if (percent) {
				char *val;
				*percent = '\0';
				val = getenv(f);
				*percent = '%';
				if (val) {
					int len = strlcpy(t, val, bufsize+1);
					if (len > bufsize)
						break;
					bufsize -= len;
					t += len;
					f = percent + 1;
					continue;
				}
			}
			f--;
		}
		*t++ = *f++;
		bufsize--;
	}
	*t = '\0';

	if (*f) {
		rprintf(FLOG, "Overflowed buf in expand_vars() trying to expand: %s\n", str);
		exit_cleanup(RERR_MALLOC);
	}

	if (bufsize && (buf = realloc(buf, t - buf + 1)) == NULL)
		out_of_memory("expand_vars");

	return buf;
}