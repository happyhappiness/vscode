	strbuf_release(&str);
	fclose(fp);

	return res;
}

static void mark_expected_rev(char *bisect_rev_hex)
{
	int len = strlen(bisect_rev_hex);
	const char *filename = git_path("BISECT_EXPECTED_REV");
	int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0600);

	if (fd < 0)
		die_errno("could not create file '%s'", filename);

	bisect_rev_hex[len] = '\n';
	write_or_die(fd, bisect_rev_hex, len + 1);
	bisect_rev_hex[len] = '\0';

	if (close(fd) < 0)
		die("closing file %s: %s", filename, strerror(errno));
}

static int bisect_checkout(char *bisect_rev_hex, int no_checkout)
{

	mark_expected_rev(bisect_rev_hex);

	argv_checkout[2] = bisect_rev_hex;
	if (no_checkout) {
		argv_update_ref[3] = bisect_rev_hex;
		if (run_command_v_opt(argv_update_ref, RUN_GIT_CMD))
			die("update-ref --no-deref HEAD failed on %s",
			    bisect_rev_hex);
	} else {
		int res;
		res = run_command_v_opt(argv_checkout, RUN_GIT_CMD);
		if (res)
			exit(res);
	}
