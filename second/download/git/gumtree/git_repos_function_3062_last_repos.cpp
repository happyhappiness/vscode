static int set_if_exists(struct conf_info *item, const char *value)
{
	if (!strcasecmp("addIfDifferent", value))
		item->if_exists = EXISTS_ADD_IF_DIFFERENT;
	else if (!strcasecmp("addIfDifferentNeighbor", value))
		item->if_exists = EXISTS_ADD_IF_DIFFERENT_NEIGHBOR;
	else if (!strcasecmp("add", value))
		item->if_exists = EXISTS_ADD;
	else if (!strcasecmp("replace", value))
		item->if_exists = EXISTS_REPLACE;
	else if (!strcasecmp("doNothing", value))
		item->if_exists = EXISTS_DO_NOTHING;
	else
		return -1;
	return 0;
}