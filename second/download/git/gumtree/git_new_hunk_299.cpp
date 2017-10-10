 * script, and thus if the file differs from what this function expects, it is
 * better to bail out than to do something that the user does not expect.
 */
static int read_author_script(struct am_state *state)
{
	const char *filename = am_path(state, "author-script");
	struct strbuf buf = STRBUF_INIT;
	struct string_list kv = STRING_LIST_INIT_DUP;
	int retval = -1; /* assume failure */
	int fd;

	assert(!state->author_name);
	assert(!state->author_email);
	assert(!state->author_date);

	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		if (errno == ENOENT)
			return 0;
		die_errno(_("could not open '%s' for reading"), filename);
	}
	strbuf_read(&buf, fd, 0);
	close(fd);
	if (parse_key_value_squoted(buf.buf, &kv))
		goto finish;

	if (kv.nr != 3 ||
	    strcmp(kv.items[0].string, "GIT_AUTHOR_NAME") ||
	    strcmp(kv.items[1].string, "GIT_AUTHOR_EMAIL") ||
	    strcmp(kv.items[2].string, "GIT_AUTHOR_DATE"))
		goto finish;
	state->author_name = kv.items[0].util;
	state->author_email = kv.items[1].util;
	state->author_date = kv.items[2].util;
	retval = 0;
finish:
	string_list_clear(&kv, !!retval);
	strbuf_release(&buf);
	return retval;
}

/**
 * Saves state->author_name, state->author_email and state->author_date in the
 * state directory's "author-script" file.
 */
