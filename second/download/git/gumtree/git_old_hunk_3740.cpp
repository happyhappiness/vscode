 * strbuf instance, which would cause the detached signature appended
 * at the end.
 */
int sign_buffer(struct strbuf *buffer, struct strbuf *signature, const char *signing_key)
{
	struct child_process gpg = CHILD_PROCESS_INIT;
	const char *args[4];
	ssize_t len;
	size_t i, j, bottom;

	gpg.argv = args;
	gpg.in = -1;
	gpg.out = -1;
	args[0] = gpg_program;
	args[1] = "-bsau";
	args[2] = signing_key;
	args[3] = NULL;

	if (start_command(&gpg))
		return error(_("could not run gpg."));

	/*
	 * When the username signingkey is bad, program could be terminated
	 * because gpg exits without reading and then write gets SIGPIPE.
	 */
	sigchain_push(SIGPIPE, SIG_IGN);

	if (write_in_full(gpg.in, buffer->buf, buffer->len) != buffer->len) {
		close(gpg.in);
		close(gpg.out);
		finish_command(&gpg);
		return error(_("gpg did not accept the data"));
	}
	close(gpg.in);

	bottom = signature->len;
	len = strbuf_read(signature, gpg.out, 1024);
	close(gpg.out);

	sigchain_pop(SIGPIPE);

	if (finish_command(&gpg) || !len || len < 0)
		return error(_("gpg failed to sign the data"));

	/* Strip CR from the line endings, in case we are on Windows. */
	for (i = j = bottom; i < signature->len; i++)
		if (signature->buf[i] != '\r') {
			if (i != j)
