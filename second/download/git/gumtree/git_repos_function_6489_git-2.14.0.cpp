static enum prefix_state overlaps_prefix(const char *dirname,
					 const char *prefix)
{
	while (*prefix && *dirname == *prefix) {
		dirname++;
		prefix++;
	}
	if (!*prefix)
		return PREFIX_CONTAINS_DIR;
	else if (!*dirname)
		return PREFIX_WITHIN_DIR;
	else
		return PREFIX_EXCLUDES_DIR;
}