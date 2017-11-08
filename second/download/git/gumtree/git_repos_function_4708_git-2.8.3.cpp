static int option_parse_space_change(const struct option *opt,
			  const char *arg, int unset)
{
	if (unset)
		ws_ignore_action = ignore_ws_none;
	else
		ws_ignore_action = ignore_ws_change;
	return 0;
}