static void parse_whitespace_option(const char *option)
{
	if (!option) {
		ws_error_action = warn_on_ws_error;
		return;
	}
	if (!strcmp(option, "warn")) {
		ws_error_action = warn_on_ws_error;
		return;
	}
	if (!strcmp(option, "nowarn")) {
		ws_error_action = nowarn_ws_error;
		return;
	}
	if (!strcmp(option, "error")) {
		ws_error_action = die_on_ws_error;
		return;
	}
	if (!strcmp(option, "error-all")) {
		ws_error_action = die_on_ws_error;
		squelch_whitespace_errors = 0;
		return;
	}
	if (!strcmp(option, "strip") || !strcmp(option, "fix")) {
		ws_error_action = correct_ws_error;
		return;
	}
	die(_("unrecognized whitespace option '%s'"), option);
}