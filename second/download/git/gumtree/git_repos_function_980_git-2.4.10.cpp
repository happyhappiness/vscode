static const char *get_accept_language(void)
{
	if (!cached_accept_language) {
		struct strbuf buf = STRBUF_INIT;
		write_accept_language(&buf);
		if (buf.len > 0)
			cached_accept_language = strbuf_detach(&buf, NULL);
	}

	return cached_accept_language;
}