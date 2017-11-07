static void parse_whitespace_option(struct apply_state *state, const char *option)
{
	if (!option) {
		state->ws_error_action = warn_on_ws_error;
		return;
	}
	if (!strcmp(option, "warn")) {
		state->ws_error_action = warn_on_ws_error;
		return;
	}
	if (!strcmp(option, "nowarn")) {
		state->ws_error_action = nowarn_ws_error;
		return;
	}
	if (!strcmp(option, "error")) {
		state->ws_error_action = die_on_ws_error;
		return;
	}
	if (!strcmp(option, "error-all")) {
		state->ws_error_action = die_on_ws_error;
		state->squelch_whitespace_errors = 0;
		return;
	}
	if (!strcmp(option, "strip") || !strcmp(option, "fix")) {
		state->ws_error_action = correct_ws_error;
		return;
	}
	die(_("unrecognized whitespace option '%s'"), option);
}