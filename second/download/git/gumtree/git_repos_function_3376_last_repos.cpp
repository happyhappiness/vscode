static int bad_request(struct strbuf *hdr, const struct service_cmd *c)
{
	const char *proto = getenv("SERVER_PROTOCOL");

	if (proto && !strcmp(proto, "HTTP/1.1")) {
		http_status(hdr, 405, "Method Not Allowed");
		hdr_str(hdr, "Allow",
			!strcmp(c->method, "GET") ? "GET, HEAD" : c->method);
	} else
		http_status(hdr, 400, "Bad Request");
	hdr_nocache(hdr);
	end_headers(hdr);
	return 0;
}