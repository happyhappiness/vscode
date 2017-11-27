int cf_read (char *filename)
{
	oconfig_item_t *conf;
	int i;

	conf = cf_read_generic (filename, /* pattern = */ NULL, /* depth = */ 0);
	if (conf == NULL)
	{
		ERROR ("Unable to read config file %s.", filename);
		return (-1);
	}
	else if (conf->children_num == 0)
	{
		ERROR ("Configuration file %s is empty.", filename);
		oconfig_free (conf);
		return (-1);
	}

	for (i = 0; i < conf->children_num; i++)
	{
		if (conf->children[i].children == NULL)
			dispatch_value (conf->children + i);
		else
			dispatch_block (conf->children + i);
	}

	oconfig_free (conf);

	/* Read the default types.db if no `TypesDB' option was given. */
	if (cf_default_typesdb)
		read_types_list (PKGDATADIR"/types.db");

	return (0);
}