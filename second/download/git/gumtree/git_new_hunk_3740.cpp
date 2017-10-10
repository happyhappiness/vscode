 * strbuf instance, which would cause the detached signature appended
 * at the end.
 */
int sign_buffer(struct strbuf *buffer, struct strbuf *signature, const char *signing_key)
{
	struct child_process gpg = CHILD_PROCESS_INIT;
	int ret;
	size_t i, j, bottom;
	struct strbuf gpg_status = STRBUF_INIT;

	argv_array_pushl(&gpg.args,
			 gpg_program,
			 "--status-fd=2",
			 "-bsau", signing_key,
			 NULL);

	bottom = signature->len;

	/*
	 * When the username signingkey is bad, program could be terminated
	 * because gpg exits without reading and then write gets SIGPIPE.
	 */
	sigchain_push(SIGPIPE, SIG_IGN);
	ret = pipe_command(&gpg, buffer->buf, buffer->len,
			   signature, 1024, &gpg_status, 0);
	sigchain_pop(SIGPIPE);

	ret |= !strstr(gpg_status.buf, "\n[GNUPG:] SIG_CREATED ");
	strbuf_release(&gpg_status);
	if (ret)
		return error(_("gpg failed to sign the data"));

	/* Strip CR from the line endings, in case we are on Windows. */
	for (i = j = bottom; i < signature->len; i++)
		if (signature->buf[i] != '\r') {
			if (i != j)
