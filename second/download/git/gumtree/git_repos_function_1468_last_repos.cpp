static void redact_sensitive_header(struct strbuf *header)
{
	const char *sensitive_header;

	if (skip_prefix(header->buf, "Authorization:", &sensitive_header) ||
	    skip_prefix(header->buf, "Proxy-Authorization:", &sensitive_header)) {
		/* The first token is the type, which is OK to log */
		while (isspace(*sensitive_header))
			sensitive_header++;
		while (*sensitive_header && !isspace(*sensitive_header))
			sensitive_header++;
		/* Everything else is opaque and possibly sensitive */
		strbuf_setlen(header,  sensitive_header - header->buf);
		strbuf_addstr(header, " <redacted>");
	}
}