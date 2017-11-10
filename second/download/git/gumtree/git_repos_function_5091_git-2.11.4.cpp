static void am_load(struct am_state *state)
{
	struct strbuf sb = STRBUF_INIT;

	if (read_state_file(&sb, state, "next", 1) < 0)
		die("BUG: state file 'next' does not exist");
	state->cur = strtol(sb.buf, NULL, 10);

	if (read_state_file(&sb, state, "last", 1) < 0)
		die("BUG: state file 'last' does not exist");
	state->last = strtol(sb.buf, NULL, 10);

	if (read_author_script(state) < 0)
		die(_("could not parse author script"));

	read_commit_msg(state);

	if (read_state_file(&sb, state, "original-commit", 1) < 0)
		oidclr(&state->orig_commit);
	else if (get_oid_hex(sb.buf, &state->orig_commit) < 0)
		die(_("could not parse %s"), am_path(state, "original-commit"));

	read_state_file(&sb, state, "threeway", 1);
	state->threeway = !strcmp(sb.buf, "t");

	read_state_file(&sb, state, "quiet", 1);
	state->quiet = !strcmp(sb.buf, "t");

	read_state_file(&sb, state, "sign", 1);
	state->signoff = !strcmp(sb.buf, "t");

	read_state_file(&sb, state, "utf8", 1);
	state->utf8 = !strcmp(sb.buf, "t");

	read_state_file(&sb, state, "keep", 1);
	if (!strcmp(sb.buf, "t"))
		state->keep = KEEP_TRUE;
	else if (!strcmp(sb.buf, "b"))
		state->keep = KEEP_NON_PATCH;
	else
		state->keep = KEEP_FALSE;

	read_state_file(&sb, state, "messageid", 1);
	state->message_id = !strcmp(sb.buf, "t");

	read_state_file(&sb, state, "scissors", 1);
	if (!strcmp(sb.buf, "t"))
		state->scissors = SCISSORS_TRUE;
	else if (!strcmp(sb.buf, "f"))
		state->scissors = SCISSORS_FALSE;
	else
		state->scissors = SCISSORS_UNSET;

	read_state_file(&sb, state, "apply-opt", 1);
	argv_array_clear(&state->git_apply_opts);
	if (sq_dequote_to_argv_array(sb.buf, &state->git_apply_opts) < 0)
		die(_("could not parse %s"), am_path(state, "apply-opt"));

	state->rebasing = !!file_exists(am_path(state, "rebasing"));

	strbuf_release(&sb);
}