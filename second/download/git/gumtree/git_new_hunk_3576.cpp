
/**
 * Saves state->msg in the state directory's "final-commit" file.
 */
static void write_commit_msg(const struct am_state *state)
{
	const char *filename = am_path(state, "final-commit");
	write_file_buf(filename, state->msg, state->msg_len);
}

/**
 * Loads state from disk.
 */
static void am_load(struct am_state *state)
