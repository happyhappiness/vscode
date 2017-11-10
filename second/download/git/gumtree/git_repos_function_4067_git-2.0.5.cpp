static void parse_ignorewhitespace_option(const char *option)
{
	if (!option || !strcmp(option, "no") ||
	    !strcmp(option, "false") || !strcmp(option, "never") ||
	    !strcmp(option, "none")) {
		ws_ignore_action = ignore_ws_none;
		return;
	}
	if (!strcmp(option, "change")) {
		ws_ignore_action = ignore_ws_change;
		return;
	}
	die(_("unrecognized whitespace ignore option '%s'"), option);
}