
		strbuf_addf(sb, " %s", hex);
	}
	strbuf_addch(sb, '\n');
}

static char *get_header(const char *msg, const char *key)
{
	size_t len;
	const char *v = find_commit_header(msg, key, &len);
	return v ? xmemdupz(v, len) : NULL;
}

static char *replace_encoding_header(char *buf, const char *encoding)
{
	struct strbuf tmp = STRBUF_INIT;
	size_t start, len;
