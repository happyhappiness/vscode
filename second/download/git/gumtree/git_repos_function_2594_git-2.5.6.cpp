static NORETURN void forbidden(const char *err, ...)
{
	va_list params;

	http_status(403, "Forbidden");
	hdr_nocache();
	end_headers();

	va_start(params, err);
	if (err && *err)
		vfprintf(stderr, err, params);
	va_end(params);
	exit(0);
}