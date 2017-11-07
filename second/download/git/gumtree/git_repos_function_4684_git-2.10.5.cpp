static void set_default_whitespace_mode(struct apply_state *state)
{
	if (!state->whitespace_option && !apply_default_whitespace)
		state->ws_error_action = (state->apply ? warn_on_ws_error : nowarn_ws_error);
}