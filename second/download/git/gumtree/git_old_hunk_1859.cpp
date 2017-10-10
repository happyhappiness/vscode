
		strbuf_addf(sb, " %s", hex);
	}
	strbuf_addch(sb, '\n');
}

static char *get_header(const struct commit *commit, const char *msg,
			const char *key)
{
	int key_len = strlen(key);
	const char *line = msg;

	while (line) {
		const char *eol = strchrnul(line, '\n'), *next;

		if (line == eol)
			return NULL;
		if (!*eol) {
			warning("malformed commit (header is missing newline): %s",
				sha1_to_hex(commit->object.sha1));
			next = NULL;
		} else
			next = eol + 1;
		if (eol - line > key_len &&
		    !strncmp(line, key, key_len) &&
		    line[key_len] == ' ') {
			return xmemdupz(line + key_len + 1, eol - line - key_len - 1);
		}
		line = next;
	}
	return NULL;
}

static char *replace_encoding_header(char *buf, const char *encoding)
{
	struct strbuf tmp = STRBUF_INIT;
	size_t start, len;
