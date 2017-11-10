static void wrap_in_html(struct strbuf *msg)
{
	struct strbuf buf = STRBUF_INIT;
	static char *content_type = "Content-Type: text/html;\n";
	static char *pre_open = "<pre>\n";
	static char *pre_close = "</pre>\n";
	const char *body = strstr(msg->buf, "\n\n");

	if (!body)
		return; /* Headers but no body; no wrapping needed */

	body += 2;

	strbuf_add(&buf, msg->buf, body - msg->buf - 1);
	strbuf_addstr(&buf, content_type);
	strbuf_addch(&buf, '\n');
	strbuf_addstr(&buf, pre_open);
	strbuf_addstr_xml_quoted(&buf, body);
	strbuf_addstr(&buf, pre_close);

	strbuf_release(msg);
	*msg = buf;
}