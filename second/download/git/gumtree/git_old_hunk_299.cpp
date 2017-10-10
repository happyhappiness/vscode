 * script, and thus if the file differs from what this function expects, it is
 * better to bail out than to do something that the user does not expect.
 */
static int read_author_script(struct am_state *state)
{
	const char *filename = am_path(state, "author-script");
	FILE *fp;

	assert(!state->author_name);
	assert(!state->author_email);
	assert(!state->author_date);

	fp = fopen(filename, "r");
	if (!fp) {
		if (errno == ENOENT)
			return 0;
		die_errno(_("could not open '%s' for reading"), filename);
	}

	state->author_name = read_shell_var(fp, "GIT_AUTHOR_NAME");
	if (!state->author_name) {
		fclose(fp);
		return -1;
	}

	state->author_email = read_shell_var(fp, "GIT_AUTHOR_EMAIL");
	if (!state->author_email) {
		fclose(fp);
		return -1;
	}

	state->author_date = read_shell_var(fp, "GIT_AUTHOR_DATE");
	if (!state->author_date) {
		fclose(fp);
		return -1;
	}

	if (fgetc(fp) != EOF) {
		fclose(fp);
		return -1;
	}

	fclose(fp);
	return 0;
}

/**
 * Saves state->author_name, state->author_email and state->author_date in the
 * state directory's "author-script" file.
 */
