static void am_state_release(struct am_state *state)
{
	free(state->dir);
	free(state->author_name);
	free(state->author_email);
	free(state->author_date);
	free(state->msg);
	argv_array_clear(&state->git_apply_opts);
}