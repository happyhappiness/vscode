static void sanitize_client(struct strbuf *out, const char *in)
{
	for (; *in; in++) {
		if (*in == '/')
			continue;
		if (*in == '.' && (!out->len || out->buf[out->len - 1] == '.'))
			continue;
		strbuf_addch(out, *in);
	}

	while (out->len && out->buf[out->len - 1] == '.')
		strbuf_setlen(out, out->len - 1);
}