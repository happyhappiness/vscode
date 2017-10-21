		 * no way to differentiate it.  The manpage mentions this. */
		if (output_motd)
			rprintf(FINFO, "%s\n", line);
	}
	kluge_around_eof = 0;

	if (rl_nulls) {
		for (i = 0; i < sargc; i++) {
			write_sbuf(f_out, sargs[i]);
			write_byte(f_out, 0);
		}
		write_byte(f_out, 0);
	} else {
		for (i = 0; i < sargc; i++)
			io_printf(f_out, "%s\n", sargs[i]);
		write_sbuf(f_out, "\n");
	}

	if (protocol_version < 23) {
		if (protocol_version == 22 || !am_sender)
			io_start_multiplex_in();
	}

	free(modname);

	return 0;
}

static char *finish_pre_exec(pid_t pid, int fd, char *request,
			     int argc, char *argv[])
{
	int j, status = -1;

	if (!request)
		request = "(NONE)";

	write_buf(fd, request, strlen(request)+1);
	for (j = 0; j < argc; j++)
		write_buf(fd, argv[j], strlen(argv[j])+1);
	write_byte(fd, 0);

	close(fd);

	if (wait_process(pid, &status, 0) < 0
	 || !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
		char *e;
		if (asprintf(&e, "pre-xfer exec returned failure (%d)%s%s\n",
			     status, status < 0 ? ": " : "",
			     status < 0 ? strerror(errno) : "") < 0)
			out_of_memory("finish_pre_exec");
		return e;
	}
	return NULL;
}

static int read_arg_from_pipe(int fd, char *buf, int limit)
{
	char *bp = buf, *eob = buf + limit - 1;

	while (1) {
	    int got = read(fd, bp, 1);
	    if (got != 1) {
		if (got < 0 && errno == EINTR)
			continue;
		return -1;
	    }
	    if (*bp == '\0')
		break;
	    if (bp < eob)
		bp++;
	}
	*bp = '\0';

	return bp - buf;
}

static int rsync_module(int f_in, int f_out, int i, char *addr, char *host)
{
	int argc, opt_cnt;
	char **argv, *chroot_path = NULL;
	char line[BIGPATHBUFLEN];
	uid_t uid = (uid_t)-2;  /* canonically "nobody" */
	gid_t gid = (gid_t)-2;
	char *p, *err_msg = NULL;
	char *name = lp_name(i);
	int use_chroot = lp_use_chroot(i);
	int ret, pre_exec_fd = -1;
	pid_t pre_exec_pid = 0;
	char *request = NULL;

#ifdef ICONV_OPTION
	iconv_opt = lp_charset(i);
	if (*iconv_opt)
		setup_iconv();
	iconv_opt = NULL;
#endif

	if (!allow_access(addr, host, lp_hosts_allow(i), lp_hosts_deny(i))) {
		rprintf(FLOG, "rsync denied on module %s from %s (%s)\n",
			name, host, addr);
		if (!lp_list(i))
			io_printf(f_out, "@ERROR: Unknown module '%s'\n", name);
		else {
