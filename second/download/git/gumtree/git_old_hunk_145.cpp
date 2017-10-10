		strbuf_setlen(pair[0], pair[0]->len - 1);
	strbuf_trim(pair[0]);
	if (!pair[0]->len) {
		strbuf_list_free(pair);
		return error("bogus config parameter: %s", text);
	}
	lowercase(pair[0]->buf);
	if (fn(pair[0]->buf, pair[1] ? pair[1]->buf : NULL, data) < 0) {
		strbuf_list_free(pair);
		return -1;
	}
	strbuf_list_free(pair);
	return 0;
