static int parse_clean_color_slot(const char *var)
{
	if (!strcasecmp(var, "reset"))
		return CLEAN_COLOR_RESET;
	if (!strcasecmp(var, "plain"))
		return CLEAN_COLOR_PLAIN;
	if (!strcasecmp(var, "prompt"))
		return CLEAN_COLOR_PROMPT;
	if (!strcasecmp(var, "header"))
		return CLEAN_COLOR_HEADER;
	if (!strcasecmp(var, "help"))
		return CLEAN_COLOR_HELP;
	if (!strcasecmp(var, "error"))
		return CLEAN_COLOR_ERROR;
	return -1;
}