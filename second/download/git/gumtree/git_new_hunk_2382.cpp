	strbuf_addf(&buf, "application/x-git-%s-result", svc->name);
	hdr_str(content_type, buf.buf);

	end_headers();

	argv[0] = svc->name;
	run_service(argv, svc->buffer_input);
	strbuf_release(&buf);
}

static int dead;
static NORETURN void die_webcgi(const char *err, va_list params)
{
	if (dead <= 1) {
		vreportf("fatal: ", err, params);

		http_status(500, "Internal Server Error");
		hdr_nocache();
		end_headers();
	}
	exit(0); /* we successfully reported a failure ;-) */
}

static int die_webcgi_recursing(void)
{
	return dead++ > 1;
}

static char* getdir(void)
{
	struct strbuf buf = STRBUF_INIT;
	char *pathinfo = getenv("PATH_INFO");
	char *root = getenv("GIT_PROJECT_ROOT");
	char *path = getenv("PATH_TRANSLATED");
