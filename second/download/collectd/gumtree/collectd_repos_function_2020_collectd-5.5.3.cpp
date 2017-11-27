static int ts_create (const oconfig_item_t *ci, void **user_data) /* {{{ */
{
	ts_data_t *data;
	int status;
	int i;

	data = (ts_data_t *) malloc (sizeof (*data));
	if (data == NULL)
	{
		ERROR ("ts_create: malloc failed.");
		return (-ENOMEM);
	}
	memset (data, 0, sizeof (*data));

	data->factor = NAN;
	data->offset = NAN;

	status = 0;
	for (i = 0; i < ci->children_num; i++)
	{
		oconfig_item_t *child = ci->children + i;

		if (strcasecmp ("Factor", child->key) == 0)
				status = ts_config_set_double (&data->factor, child);
		else if (strcasecmp ("Offset", child->key) == 0)
				status = ts_config_set_double (&data->offset, child);
		else if (strcasecmp ("DataSource", child->key) == 0)
				status = ts_config_add_data_source(data, child);
		else
		{
			ERROR ("Target `scale': The `%s' configuration option is not understood "
					"and will be ignored.", child->key);
			status = 0;
		}

		if (status != 0)
			break;
	}

	/* Additional sanity-checking */
	while (status == 0)
	{
		if (isnan (data->factor) && isnan (data->offset))
		{
			ERROR ("Target `scale': You need to at least set either the `Factor' "
					"or `Offset' option!");
			status = -1;
		}

		break;
	}

	if (status != 0)
	{
		ts_destroy ((void *) &data);
		return (status);
	}

	*user_data = data;
	return (0);
}