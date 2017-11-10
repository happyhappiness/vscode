static int save_state(unsigned char *stash)
{
	int len;
	struct child_process cp = CHILD_PROCESS_INIT;
	struct strbuf buffer = STRBUF_INIT;
	const char *argv[] = {"stash", "create", NULL};

	cp.argv = argv;
	cp.out = -1;
	cp.git_cmd = 1;

	if (start_command(&cp))
		die(_("could not run stash."));
	len = strbuf_read(&buffer, cp.out, 1024);
	close(cp.out);

	if (finish_command(&cp) || len < 0)
		die(_("stash failed"));
	else if (!len)		/* no changes */
		return -1;
	strbuf_setlen(&buffer, buffer.len-1);
	if (get_sha1(buffer.buf, stash))
		die(_("not a valid object: %s"), buffer.buf);
	return 0;
}