static int read_commit_msg(struct am_state *state)
{
	struct strbuf sb = STRBUF_INIT;

	assert(!state->msg);

	if (read_state_file(&sb, state, "final-commit", 0) < 0) {
		strbuf_release(&sb);
		return -1;
	}

	state->msg = strbuf_detach(&sb, &state->msg_len);
	return 0;
}