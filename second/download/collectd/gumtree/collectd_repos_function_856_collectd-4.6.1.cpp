static int cf_include_all (oconfig_item_t *root, int depth)
{
	int i;

	for (i = 0; i < root->children_num; i++)
	{
		oconfig_item_t *new;
		oconfig_item_t *old;

		/* Ignore all blocks, including `Include' blocks. */
		if (root->children[i].children_num != 0)
			continue;

		if (strcasecmp (root->children[i].key, "Include") != 0)
			continue;

		old = root->children + i;

		if ((old->values_num != 1)
				|| (old->values[0].type != OCONFIG_TYPE_STRING))
		{
			ERROR ("configfile: `Include' needs exactly one string argument.");
			continue;
		}

		new = cf_read_generic (old->values[0].value.string, depth + 1);
		if (new == NULL)
			continue;

		/* Now replace the i'th child in `root' with `new'. */
		cf_ci_replace_child (root, new, i);

		sfree (new->values);
		sfree (new);
	} /* for (i = 0; i < root->children_num; i++) */

	return (0);
}