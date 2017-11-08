static void curl_dump_header(const char *text, unsigned char *ptr, size_t size, int hide_sensitive_header)
{
	struct strbuf out = STRBUF_INIT;
	struct strbuf **headers, **header;

	strbuf_addf(&out, "%s, %10.10ld bytes (0x%8.8lx)\n",
		text, (long)size, (long)size);
	trace_strbuf(&trace_curl, &out);
	strbuf_reset(&out);
	strbuf_add(&out, ptr, size);
	headers = strbuf_split_max(&out, '\n', 0);

	for (header = headers; *header; header++) {
		if (hide_sensitive_header)
			redact_sensitive_header(*header);
		strbuf_insert((*header), 0, text, strlen(text));
		strbuf_insert((*header), strlen(text), ": ", 2);
		strbuf_rtrim((*header));
		strbuf_addch((*header), '\n');
		trace_strbuf(&trace_curl, (*header));
	}
	strbuf_list_free(headers);
	strbuf_release(&out);
}