static int check_cert_push_options(const struct string_list *push_options)
{
	const char *buf = push_cert.buf;
	int len = push_cert.len;

	char *option;
	const char *next_line;
	int options_seen = 0;

	int retval = 1;

	if (!len)
		return 1;

	while ((option = find_header(buf, len, "push-option", &next_line))) {
		len -= (next_line - buf);
		buf = next_line;
		options_seen++;
		if (options_seen > push_options->nr
		    || strcmp(option,
			      push_options->items[options_seen - 1].string)) {
			retval = 0;
			goto leave;
		}
		free(option);
	}

	if (options_seen != push_options->nr)
		retval = 0;

leave:
	free(option);
	return retval;
}