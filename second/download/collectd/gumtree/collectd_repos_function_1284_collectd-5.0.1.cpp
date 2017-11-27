static oconfig_item_t *cf_read_generic (const char *path, int depth)
{
	oconfig_item_t *root = NULL;
	int status;
	const char *path_ptr;
	wordexp_t we;
	size_t i;

	if (depth >= CF_MAX_DEPTH)
	{
		ERROR ("configfile: Not including `%s' because the maximum "
				"nesting depth has been reached.", path);
		return (NULL);
	}

	status = wordexp (path, &we, WRDE_NOCMD);
	if (status != 0)
	{
		ERROR ("configfile: wordexp (%s) failed.", path);
		return (NULL);
	}

	root = (oconfig_item_t *) malloc (sizeof (oconfig_item_t));
	if (root == NULL)
	{
		ERROR ("configfile: malloc failed.");
		return (NULL);
	}
	memset (root, '\0', sizeof (oconfig_item_t));

	/* wordexp() might return a sorted list already. That's not
	 * documented though, so let's make sure we get what we want. */
	qsort ((void *) we.we_wordv, we.we_wordc, sizeof (*we.we_wordv),
			cf_compare_string);

	for (i = 0; i < we.we_wordc; i++)
	{
		oconfig_item_t *temp;
		struct stat statbuf;

		path_ptr = we.we_wordv[i];

		status = stat (path_ptr, &statbuf);
		if (status != 0)
		{
			char errbuf[1024];
			WARNING ("configfile: stat (%s) failed: %s",
					path_ptr,
					sstrerror (errno, errbuf, sizeof (errbuf)));
			continue;
		}

		if (S_ISREG (statbuf.st_mode))
			temp = cf_read_file (path_ptr, depth);
		else if (S_ISDIR (statbuf.st_mode))
			temp = cf_read_dir (path_ptr, depth);
		else
		{
			WARNING ("configfile: %s is neither a file nor a "
					"directory.", path);
			continue;
		}

		if (temp == NULL) {
			oconfig_free (root);
			return (NULL);
		}

		cf_ci_append_children (root, temp);
		sfree (temp->children);
		sfree (temp);
	}

	wordfree (&we);

	if (root->children == NULL)
	{
		oconfig_free (root);
		return (NULL);
	}

	return (root);
}