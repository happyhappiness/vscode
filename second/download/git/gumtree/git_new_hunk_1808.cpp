	const char *config_name;
	daemon_service_fn fn;
	int enabled;
	int overridable;
};

static int daemon_error(const char *dir, const char *msg)
{
	if (!informative_errors)
		msg = "access denied or repository not exported";
	packet_write(1, "ERR %s: %s", msg, dir);
	return -1;
}

static const char *access_hook;

static int run_access_hook(struct daemon_service *service, const char *dir, const char *path)
{
	struct child_process child = CHILD_PROCESS_INIT;
	struct strbuf buf = STRBUF_INIT;
	const char *argv[8];
	const char **arg = argv;
	char *eol;
	int seen_errors = 0;

