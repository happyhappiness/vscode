static void am_next(struct am_state *state)
{
	struct object_id head;

	FREE_AND_NULL(state->author_name);
	FREE_AND_NULL(state->author_email);
	FREE_AND_NULL(state->author_date);
	FREE_AND_NULL(state->msg);
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