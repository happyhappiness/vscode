 */
int verify_signed_buffer(const char *payload, size_t payload_size,
			 const char *signature, size_t signature_size,
			 struct strbuf *gpg_output, struct strbuf *gpg_status)
{
	struct child_process gpg = CHILD_PROCESS_INIT;
	static struct tempfile temp;
	int fd, ret;
	struct strbuf buf = STRBUF_INIT;

	fd = mks_tempfile_t(&temp, ".git_vtag_tmpXXXXXX");
	if (fd < 0)
		return error_errno(_("could not create temporary file"));
	if (write_in_full(fd, signature, signature_size) < 0) {
		error_errno(_("failed writing detached signature to '%s'"),
			    temp.filename.buf);
		delete_tempfile(&temp);
		return -1;
	}
	close(fd);

	argv_array_pushl(&gpg.args,
			 gpg_program,
			 "--status-fd=1",
			 "--keyid-format=long",
			 "--verify", temp.filename.buf, "-",
			 NULL);

	if (!gpg_status)
		gpg_status = &buf;

	sigchain_push(SIGPIPE, SIG_IGN);
	ret = pipe_command(&gpg, payload, payload_size,
			   gpg_status, 0, gpg_output, 0);
	sigchain_pop(SIGPIPE);

	delete_tempfile(&temp);

	ret |= !strstr(gpg_status->buf, "\n[GNUPG:] GOODSIG ");
	strbuf_release(&buf); /* no matter it was used or not */

	return ret;
}
