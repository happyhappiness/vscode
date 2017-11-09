static NORETURN void forbidden(struct strbuf *hdr, const char *err, ...)
{
	va_list params;

	http_status(hdr, 403, "Forbidden");
	hdr_nocache(hdr);
	end_headers(hdr);

	va_start(params, err);
	if (err && *err)
		vfprintf(stderr, err, params);
	va_end(params);
	exit(0);
}