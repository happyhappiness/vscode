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

		new = cf_read_file (old->values[0].value.string, depth + 1);
		if (new == NULL)
			continue;

		/* There are more children now. We need to expand
		 * root->children. */
		if (new->children_num > 1)
		{
			oconfig_item_t *temp;

			DEBUG ("configfile: Resizing root-children from %i to %i elements.",
					root->children_num,
					root->children_num + new->children_num - 1);

			temp = (oconfig_item_t *) realloc (root->children,
					sizeof (oconfig_item_t)
					* (root->children_num + new->children_num - 1));
			if (temp == NULL)
			{
				ERROR ("configfile: realloc failed.");
				oconfig_free (new);
				continue;
			}
			root->children = temp;
		}

		/* Clean up the old include directive while we still have a
		 * valid pointer */
		DEBUG ("configfile: Cleaning up `old'");
		/* sfree (old->values[0].value.string); */
		sfree (old->values);

		/* If there are trailing children and the number of children
		 * changes, we need to move the trailing ones either one to the
		 * front or (new->num - 1) to the back */
		if (((root->children_num - i) > 1)
				&& (new->children_num != 1))
		{
			DEBUG ("configfile: Moving trailing children.");
			memmove (root->children + i + new->children_num,
					root->children + i + 1,
					sizeof (oconfig_item_t)
					* (root->children_num - (i + 1)));
		}

		/* Now copy the new children to where the include statement was */
		if (new->children_num > 0)
		{
			DEBUG ("configfile: Copying new children.");
			memcpy (root->children + i,
					new->children,
					sizeof (oconfig_item_t)
					* new->children_num);
		}

		/* Adjust the number of children and the position in the list. */
		root->children_num = root->children_num + new->children_num - 1;
		i = i + new->children_num - 1;

		/* Clean up the `new' struct. We set `new->children' to NULL so
		 * the stuff we've just copied pointers to isn't freed by
		 * `oconfig_free' */
		DEBUG ("configfile: Cleaning up `new'");
		sfree (new->values); /* should be NULL anyway */
		sfree (new);
		new = NULL;
	} /* for (i = 0; i < root->children_num; i++) */

	return (0);
}