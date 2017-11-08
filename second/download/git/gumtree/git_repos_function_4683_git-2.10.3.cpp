static void parse_ignorewhitespace_option(struct apply_state *state,
					  const char *option)
{
	if (!option || !strcmp(option, "no") ||
	    !strcmp(option, "false") || !strcmp(option, "never") ||
	    !strcmp(option, "none")) {
		state->ws_ignore_action = ignore_ws_none;
		return;
	}
	if (!strcmp(option, "change")) {
		state->ws_ignore_action = ignore_ws_change;
		return;
	}
	die(_("unrecognized whitespace ignore option '%s'"), option);
}