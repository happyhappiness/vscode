	for (p = packed_git; p; p = p->next) {
		if (p->pack_local)
			strbuf_addf(&buf, "P %s\n", p->pack_name + objdirlen + 6);
	}
	strbuf_addch(&buf, '\n');

	hdr_nocache();
	send_strbuf("text/plain; charset=utf-8", &buf);
	strbuf_release(&buf);
}

static void check_content_type(const char *accepted_type)
{
	const char *actual_type = getenv("CONTENT_TYPE");

	if (!actual_type)
		actual_type = "";

	if (strcmp(actual_type, accepted_type)) {
		http_status(415, "Unsupported Media Type");
		hdr_nocache();
		end_headers();
		format_write(1,
			"Expected POST with Content-Type '%s',"
			" but received '%s' instead.\n",
			accepted_type, actual_type);
		exit(0);
	}
}

static void service_rpc(char *service_name)
{
	const char *argv[] = {NULL, "--stateless-rpc", ".", NULL};
	struct rpc_service *svc = select_service(service_name);
	struct strbuf buf = STRBUF_INIT;

	strbuf_reset(&buf);
	strbuf_addf(&buf, "application/x-git-%s-request", svc->name);
	check_content_type(buf.buf);

	hdr_nocache();

	strbuf_reset(&buf);
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
