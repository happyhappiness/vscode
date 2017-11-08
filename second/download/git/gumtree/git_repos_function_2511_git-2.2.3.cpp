static NORETURN void die_webcgi(const char *err, va_list params)
{
	static int dead;

	if (!dead) {
		dead = 1;
		http_status(500, "Internal Server Error");
		hdr_nocache();
		end_headers();

		vreportf("fatal: ", err, params);
	}
	exit(0); /* we successfully reported a failure ;-) */
}