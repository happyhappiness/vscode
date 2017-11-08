int verify_signed_buffer(const char *payload, size_t payload_size,
			 const char *signature, size_t signature_size,
			 struct strbuf *gpg_output, struct strbuf *gpg_status)
{
	struct child_process gpg = CHILD_PROCESS_INIT;
	const char *args_gpg[] = {NULL, "--status-fd=1", "--verify", "FILE", "-", NULL};
	char path[PATH_MAX];
	int fd, ret;
	struct strbuf buf = STRBUF_INIT;
	struct strbuf *pbuf = &buf;

	args_gpg[0] = gpg_program;
	fd = git_mkstemp(path, PATH_MAX, ".git_vtag_tmpXXXXXX");
	if (fd < 0)
		return error_errno(_("could not create temporary file '%s'"), path);
	if (write_in_full(fd, signature, signature_size) < 0)
		return error_errno(_("failed writing detached signature to '%s'"), path);
	close(fd);

	gpg.argv = args_gpg;
	gpg.in = -1;
	gpg.out = -1;
	if (gpg_output)
		gpg.err = -1;
	args_gpg[3] = path;
	if (start_command(&gpg)) {
		unlink(path);
		return error(_("could not run gpg."));
	}

	sigchain_push(SIGPIPE, SIG_IGN);
	write_in_full(gpg.in, payload, payload_size);
	close(gpg.in);

	if (gpg_output) {
		strbuf_read(gpg_output, gpg.err, 0);
		close(gpg.err);
	}
	if (gpg_status)
		pbuf = gpg_status;
	strbuf_read(pbuf, gpg.out, 0);
	close(gpg.out);

	ret = finish_command(&gpg);
	sigchain_pop(SIGPIPE);

	unlink_or_warn(path);

	ret |= !strstr(pbuf->buf, "\n[GNUPG:] GOODSIG ");
	strbuf_release(&buf); /* no matter it was used or not */

	return ret;
}