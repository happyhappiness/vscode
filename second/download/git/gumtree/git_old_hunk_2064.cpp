	errno = EACCES;
	daemon_error(dir, buf.buf);
	strbuf_release(&buf);
	return -1;
}

static int run_service(const char *dir, struct daemon_service *service)
{
	const char *path;
	int enabled = service->enabled;
	struct strbuf var = STRBUF_INIT;

	loginfo("Request %s for '%s'", service->name, dir);
