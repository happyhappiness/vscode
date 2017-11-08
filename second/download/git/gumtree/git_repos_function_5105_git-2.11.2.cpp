static void am_next(struct am_state *state)
{
	struct object_id head;

	free(state->author_name);
	state->author_name = NULL;

	free(state->author_email);
	state->author_email = NULL;

	free(state->author_date);
	state->author_date = NULL;

	free(state->msg);
	state->msg = NULL;
	state->msg_len = 0;

	unlink(am_path(state, "author-script"));
	unlink(am_path(state, "final-commit"));

	oidclr(&state->orig_commit);
	unlink(am_path(state, "original-commit"));

	if (!get_oid("HEAD", &head))
		write_state_text(state, "abort-safety", oid_to_hex(&head));
	else
		write_state_text(state, "abort-safety", "");

	state->cur++;
	write_state_count(state, "next", state->cur);
}