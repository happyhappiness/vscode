static NORETURN void die_webcgi(const char *err, va_list params)
{
	if (dead <= 1) {
		struct strbuf hdr = STRBUF_INIT;

		vreportf("fatal: ", err, params);

		http_status(&hdr, 500, "Internal Server Error");
		hdr_nocache(&hdr);
		end_headers(&hdr);
	}
	exit(0); /* we successfully reported a failure ;-) */
}