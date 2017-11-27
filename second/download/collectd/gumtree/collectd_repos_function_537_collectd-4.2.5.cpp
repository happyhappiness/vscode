static oconfig_item_t *cf_read_file (const char *file, int depth)
{
	oconfig_item_t *root;

	if (depth >= CF_MAX_DEPTH)
	{
		ERROR ("configfile: Not including `%s' because the maximum nesting depth has been reached.",
				file);
		return (NULL);
	}

	root = oconfig_parse_file (file);
	if (root == NULL)
	{
		ERROR ("configfile: Cannot read file `%s'.", file);
		return (NULL);
	}

	cf_include_all (root, depth);

	return (root);
}