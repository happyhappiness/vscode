static void am_state_init(struct am_state *state, const char *dir)
{
	int gpgsign;

	memset(state, 0, sizeof(*state));

	assert(dir);
	state->dir = xstrdup(dir);

	state->prec = 4;

	git_config_get_bool("am.threeway", &state->threeway);

	state->utf8 = 1;

	git_config_get_bool("am.messageid", &state->message_id);

	state->scissors = SCISSORS_UNSET;

	argv_array_init(&state->git_apply_opts);

	if (!git_config_get_bool("commit.gpgsign", &gpgsign))
		state->sign_commit = gpgsign ? "" : NULL;
}