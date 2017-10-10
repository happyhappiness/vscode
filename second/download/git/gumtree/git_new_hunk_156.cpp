	if (!informative_errors)
		msg = "access denied or repository not exported";
	packet_write(1, "ERR %s: %s", msg, dir);
	return -1;
}

static const char *access_hook;

static int run_access_hook(struct daemon_service *service, const char *dir, const char *path)
{
	struct child_process child;
	struct strbuf buf = STRBUF_INIT;
	const char *argv[8];
