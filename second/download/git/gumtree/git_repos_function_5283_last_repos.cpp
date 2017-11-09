static int run_rewrite_hook(const struct object_id *oldoid,
			    const struct object_id *newoid)
{
	struct child_process proc = CHILD_PROCESS_INIT;
	const char *argv[3];
	int code;
	struct strbuf sb = STRBUF_INIT;

	argv[0] = find_hook("post-rewrite");
	if (!argv[0])
		return 0;

	argv[1] = "amend";
	argv[2] = NULL;

	proc.argv = argv;
	proc.in = -1;
	proc.stdout_to_stderr = 1;

	code = start_command(&proc);
	if (code)
		return code;
	strbuf_addf(&sb, "%s %s\n", oid_to_hex(oldoid), oid_to_hex(newoid));
	sigchain_push(SIGPIPE, SIG_IGN);
	write_in_full(proc.in, sb.buf, sb.len);
	close(proc.in);
	strbuf_release(&sb);
	sigchain_pop(SIGPIPE);
	return finish_command(&proc);
}