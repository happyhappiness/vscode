static int value_list_to_string (char *buffer, int buffer_len,
		const data_set_t *ds, const value_list_t *vl)
{
	int offset;
	int status;
	gauge_t *rates = NULL;

	assert (0 == strcmp (ds->type, vl->type));

	memset (buffer, '\0', buffer_len);

	status = ssnprintf (buffer, buffer_len, "%.3f",
			CDTIME_T_TO_DOUBLE (vl->time));
	if ((status < 1) || (status >= buffer_len))
		return (-1);
	offset = status;

	for (size_t i = 0; i < ds->ds_num; i++)
	{
		if ((ds->ds[i].type != DS_TYPE_COUNTER)
				&& (ds->ds[i].type != DS_TYPE_GAUGE)
				&& (ds->ds[i].type != DS_TYPE_DERIVE)
				&& (ds->ds[i].type != DS_TYPE_ABSOLUTE))
		{
			sfree (rates);
			return (-1);
		}

		if (ds->ds[i].type == DS_TYPE_GAUGE)
		{
			status = ssnprintf (buffer + offset, buffer_len - offset,
					",%lf", vl->values[i].gauge);
		}
		else if (store_rates != 0)
		{
			if (rates == NULL)
				rates = uc_get_rate (ds, vl);
			if (rates == NULL)
			{
				WARNING ("csv plugin: "
						"uc_get_rate failed.");
				return (-1);
			}
			status = ssnprintf (buffer + offset,
					buffer_len - offset,
					",%lf", rates[i]);
		}
		else if (ds->ds[i].type == DS_TYPE_COUNTER)
		{
			status = ssnprintf (buffer + offset,
					buffer_len - offset,
					",%llu",
					vl->values[i].counter);
		}
		else if (ds->ds[i].type == DS_TYPE_DERIVE)
		{
			status = ssnprintf (buffer + offset,
					buffer_len - offset,
					",%"PRIi64,
					vl->values[i].derive);
		}
		else if (ds->ds[i].type == DS_TYPE_ABSOLUTE)
		{
			status = ssnprintf (buffer + offset,
					buffer_len - offset,
					",%"PRIu64,
					vl->values[i].absolute);
		}

		if ((status < 1) || (status >= (buffer_len - offset)))
		{
			sfree (rates);
			return (-1);
		}

		offset += status;
	} /* for ds->ds_num */

	sfree (rates);
	return (0);
}