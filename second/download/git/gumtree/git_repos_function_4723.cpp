static int parse_branch_color_slot(const char *slot)
{
	if (!strcasecmp(slot, "plain"))
		return BRANCH_COLOR_PLAIN;
	if (!strcasecmp(slot, "reset"))
		return BRANCH_COLOR_RESET;
	if (!strcasecmp(slot, "remote"))
		return BRANCH_COLOR_REMOTE;
	if (!strcasecmp(slot, "local"))
		return BRANCH_COLOR_LOCAL;
	if (!strcasecmp(slot, "current"))
		return BRANCH_COLOR_CURRENT;
	if (!strcasecmp(slot, "upstream"))
		return BRANCH_COLOR_UPSTREAM;
	return -1;
}