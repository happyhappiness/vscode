static void write_commit_msg(const struct am_state *state)
{
	const char *filename = am_path(state, "final-commit");
	write_file_buf(filename, state->msg, state->msg_len);
}