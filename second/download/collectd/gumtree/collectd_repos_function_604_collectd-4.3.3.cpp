static oconfig_item_t *cf_read_file (const char *file, int depth)
{
	oconfig_item_t *root;

	assert (depth < CF_MAX_DEPTH);

	root = oconfig_parse_file (file);
	if (root == NULL)
	{
		ERROR ("configfile: Cannot read file `%s'.", file);
		return (NULL);
	}

	cf_include_all (root, depth);

	return (root);
}