void str_end_url_with_slash(const char *url, char **dest) {
	struct strbuf buf = STRBUF_INIT;
	end_url_with_slash(&buf, url);
	free(*dest);
	*dest = strbuf_detach(&buf, NULL);
}