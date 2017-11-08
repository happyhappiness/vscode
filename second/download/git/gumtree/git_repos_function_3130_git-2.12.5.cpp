static NORETURN void not_found(struct strbuf *hdr, const char *err, ...)
{
	va_list params;

	http_status(hdr, 404, "Not Found");
	hdr_nocache(hdr);
	end_headers(hdr);

	va_start(params, err);
	if (err && *err)
		vfprintf(stderr, err, params);
	va_end(params);
	exit(0);
}