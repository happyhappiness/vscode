static int write_author_script(const char *message)
{
	struct strbuf buf = STRBUF_INIT;
	const char *eol;
	int res;

	for (;;)
		if (!*message || starts_with(message, "\n")) {
missing_author:
			/* Missing 'author' line? */
			unlink(rebase_path_author_script());
			return 0;
		} else if (skip_prefix(message, "author ", &message))
			break;
		else if ((eol = strchr(message, '\n')))
			message = eol + 1;
		else
			goto missing_author;

	strbuf_addstr(&buf, "GIT_AUTHOR_NAME='");
	while (*message && *message != '\n' && *message != '\r')
		if (skip_prefix(message, " <", &message))
			break;
		else if (*message != '\'')
			strbuf_addch(&buf, *(message++));
		else
			strbuf_addf(&buf, "'\\\\%c'", *(message++));
	strbuf_addstr(&buf, "'\nGIT_AUTHOR_EMAIL='");
	while (*message && *message != '\n' && *message != '\r')
		if (skip_prefix(message, "> ", &message))
			break;
		else if (*message != '\'')
			strbuf_addch(&buf, *(message++));
		else
			strbuf_addf(&buf, "'\\\\%c'", *(message++));
	strbuf_addstr(&buf, "'\nGIT_AUTHOR_DATE='@");
	while (*message && *message != '\n' && *message != '\r')
		if (*message != '\'')
			strbuf_addch(&buf, *(message++));
		else
			strbuf_addf(&buf, "'\\\\%c'", *(message++));
	res = write_message(buf.buf, buf.len, rebase_path_author_script(), 1);
	strbuf_release(&buf);
	return res;
}