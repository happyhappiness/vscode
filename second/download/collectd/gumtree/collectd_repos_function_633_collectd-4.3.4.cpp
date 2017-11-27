int handle_putval (FILE *fh, char **fields, int fields_num)
{
	char *hostname;
	char *plugin;
	char *plugin_instance;
	char *type;
	char *type_instance;
	int   status;
	int   i;

	char *identifier_copy;

	const data_set_t *ds;
	value_list_t vl = VALUE_LIST_INIT;

	if (fields_num < 3)
	{
		DEBUG ("cmd putval: Wrong number of fields: %i",
			       	fields_num);
		fprintf (fh, "-1 Wrong number of fields: Got %i, "
				"expected at least 3.\n",
				fields_num);
		fflush (fh);
		return (-1);
	}

	/* parse_identifier() modifies its first argument,
	 * returning pointers into it */
	identifier_copy = sstrdup (fields[1]);

	status = parse_identifier (identifier_copy, &hostname,
			&plugin, &plugin_instance,
			&type, &type_instance);
	if (status != 0)
	{
		DEBUG ("cmd putval: Cannot parse `%s'", fields[1]);
		fprintf (fh, "-1 Cannot parse identifier.\n");
		fflush (fh);
		sfree (identifier_copy);
		return (-1);
	}

	if ((strlen (hostname) >= sizeof (vl.host))
			|| (strlen (plugin) >= sizeof (vl.plugin))
			|| ((plugin_instance != NULL)
				&& (strlen (plugin_instance) >= sizeof (vl.plugin_instance)))
			|| ((type_instance != NULL)
				&& (strlen (type_instance) >= sizeof (vl.type_instance))))
	{
		fprintf (fh, "-1 Identifier too long.\n");
		fflush (fh);
		sfree (identifier_copy);
		return (-1);
	}

	sstrncpy (vl.host, hostname, sizeof (vl.host));
	sstrncpy (vl.plugin, plugin, sizeof (vl.plugin));
	if (plugin_instance != NULL)
		sstrncpy (vl.plugin_instance, plugin_instance, sizeof (vl.plugin_instance));
	if (type_instance != NULL)
		sstrncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

	ds = plugin_get_ds (type);
	if (ds == NULL) {
		sfree (identifier_copy);
		return (-1);
	}

	vl.values_len = ds->ds_num;
	vl.values = (value_t *) malloc (vl.values_len * sizeof (value_t));
	if (vl.values == NULL)
	{
		fprintf (fh, "-1 malloc failed.\n");
		fflush (fh);
		sfree (identifier_copy);
		return (-1);
	}

	/* All the remaining fields are part of the optionlist. */
	for (i = 2; i < fields_num; i++)
	{
		if (strchr (fields[i], ':') != NULL)
		{
			/* It's parse_value's job to write an error to `fh'.
			 * This is not the case with `parse_option below.
			 * Neither will write an success message. */
			if (parse_value (ds, &vl, type, fh, fields[i]) != 0)
				break;
		}
		else if (strchr (fields[i], '=') != NULL)
		{
			if (parse_option (&vl, fields[i]) != 0)
			{
				fprintf (fh, "-1 Error parsing option `%s'\n",
						fields[i]);
				break;
			}
		}
		else
		{
			WARNING ("cmd putval: handle_putval: "
					"Cannot parse field #%i `%s'; "
					"Ignoring it.\n",
					i, fields[i]);
		}
	}
	/* Done parsing the options. */

	if (i == fields_num)
		fprintf (fh, "0 Success\n");
	fflush (fh);

	sfree (vl.values); 
	sfree (identifier_copy);

	return (0);
}