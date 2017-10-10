
/**
 * Saves state->msg in the state directory's "final-commit" file.
 */
static void write_commit_msg(const struct am_state *state)
{
	int fd;
	const char *filename = am_path(state, "final-commit");

	fd = xopen(filename, O_WRONLY | O_CREAT, 0666);
	if (write_in_full(fd, state->msg, state->msg_len) < 0)
		die_errno(_("could not write to %s"), filename);
	close(fd);
}

/**
 * Loads state from disk.
 */
static void am_load(struct am_state *state)
