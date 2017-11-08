static int parse_diff_color_slot(const char *var)
{
	if (!strcasecmp(var, "context") || !strcasecmp(var, "plain"))
		return DIFF_CONTEXT;
	if (!strcasecmp(var, "meta"))
		return DIFF_METAINFO;
	if (!strcasecmp(var, "frag"))
		return DIFF_FRAGINFO;
	if (!strcasecmp(var, "old"))
		return DIFF_FILE_OLD;
	if (!strcasecmp(var, "new"))
		return DIFF_FILE_NEW;
	if (!strcasecmp(var, "commit"))
		return DIFF_COMMIT;
	if (!strcasecmp(var, "whitespace"))
		return DIFF_WHITESPACE;
	if (!strcasecmp(var, "func"))
		return DIFF_FUNCINFO;
	return -1;
}