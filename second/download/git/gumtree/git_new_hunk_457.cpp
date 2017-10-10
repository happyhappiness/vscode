};

static int daemon_error(const char *dir, const char *msg)
{
	if (!informative_errors)
		msg = "access denied or repository not exported";
	packet_write_fmt(1, "ERR %s: %s", msg, dir);
	return -1;
}

static const char *access_hook;

static int run_access_hook(struct daemon_service *service, const char *dir,
