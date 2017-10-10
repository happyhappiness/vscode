	errno = EACCES;
	daemon_error(dir, buf.buf);
	strbuf_release(&buf);
	return -1;
}

static int run_service(char *dir, struct daemon_service *service)
{
	const char *path;
	int enabled = service->enabled;

	loginfo("Request %s for '%s'", service->name, dir);

