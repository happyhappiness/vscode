static char *find_header(const char *msg, size_t len, const char *key,
			 const char **next_line)
{
	int key_len = strlen(key);
	const char *line = msg;

	while (line && line < msg + len) {
		const char *eol = strchrnul(line, '\n');

		if ((msg + len <= eol) || line == eol)
			return NULL;
		if (line + key_len < eol &&
		    !memcmp(line, key, key_len) && line[key_len] == ' ') {
			int offset = key_len + 1;
			if (next_line)
				*next_line = *eol ? eol + 1 : eol;
			return xmemdupz(line + offset, (eol - line) - offset);
		}
		line = *eol ? eol + 1 : NULL;
	}
	return NULL;
}