static int parse_branch_color_slot(const char *var, int ofs)
{
	if (!strcasecmp(var+ofs, "plain"))
		return BRANCH_COLOR_PLAIN;
	if (!strcasecmp(var+ofs, "reset"))
		return BRANCH_COLOR_RESET;
	if (!strcasecmp(var+ofs, "remote"))
		return BRANCH_COLOR_REMOTE;
	if (!strcasecmp(var+ofs, "local"))
		return BRANCH_COLOR_LOCAL;
	if (!strcasecmp(var+ofs, "current"))
		return BRANCH_COLOR_CURRENT;
	if (!strcasecmp(var+ofs, "upstream"))
		return BRANCH_COLOR_UPSTREAM;
	return -1;
}