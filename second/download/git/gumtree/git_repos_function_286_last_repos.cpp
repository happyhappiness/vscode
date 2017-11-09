static void do_cache(const char *socket, const char *action, int timeout,
		     int flags)
{
	struct strbuf buf = STRBUF_INIT;

	strbuf_addf(&buf, "action=%s\n", action);
	strbuf_addf(&buf, "timeout=%d\n", timeout);
	if (flags & FLAG_RELAY) {
		if (strbuf_read(&buf, 0, 0) < 0)
			die_errno("unable to relay credential");
	}

	if (send_request(socket, &buf) < 0) {
		if (errno != ENOENT && errno != ECONNREFUSED)
			die_errno("unable to connect to cache daemon");
		if (flags & FLAG_SPAWN) {
			spawn_daemon(socket);
			if (send_request(socket, &buf) < 0)
				die_errno("unable to connect to cache daemon");
		}
	}
	strbuf_release(&buf);
}