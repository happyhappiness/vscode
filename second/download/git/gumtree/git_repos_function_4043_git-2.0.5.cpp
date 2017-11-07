static int run_rewrite_hook(const unsigned char *oldsha1,
			    const unsigned char *newsha1)
{
	/* oldsha1 SP newsha1 LF NUL */
	static char buf[2*40 + 3];
	struct child_process proc;
	const char *argv[3];
	int code;
	size_t n;

	argv[0] = find_hook("post-rewrite");
	if (!argv[0])
		return 0;

	argv[1] = "amend";
	argv[2] = NULL;

	memset(&proc, 0, sizeof(proc));
	proc.argv = argv;
	proc.in = -1;
	proc.stdout_to_stderr = 1;

	code = start_command(&proc);
	if (code)
		return code;
	n = snprintf(buf, sizeof(buf), "%s %s\n",
		     sha1_to_hex(oldsha1), sha1_to_hex(newsha1));
	write_in_full(proc.in, buf, n);
	close(proc.in);
	return finish_command(&proc);
}