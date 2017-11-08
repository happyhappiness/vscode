static void spawn_daemon(const char *socket)
{
	struct child_process daemon = CHILD_PROCESS_INIT;
	const char *argv[] = { NULL, NULL, NULL };
	char buf[128];
	int r;

	argv[0] = "git-credential-cache--daemon";
	argv[1] = socket;
	daemon.argv = argv;
	daemon.no_stdin = 1;
	daemon.out = -1;

	if (start_command(&daemon))
		die_errno("unable to start cache daemon");
	r = read_in_full(daemon.out, buf, sizeof(buf));
	if (r < 0)
		die_errno("unable to read result code from cache daemon");
	if (r != 3 || memcmp(buf, "ok\n", 3))
		die("cache daemon did not start: %.*s", r, buf);
	close(daemon.out);
}