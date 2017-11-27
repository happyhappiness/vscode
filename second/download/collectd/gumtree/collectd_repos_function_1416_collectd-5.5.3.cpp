static int value_list_to_string (char *buffer, int buffer_len,
		const data_set_t *ds, const value_list_t *vl)
{
	int status;
	time_t tt;

	if (ds->ds_num != 1)
		return (value_list_to_string_multiple (buffer, buffer_len,
					ds, vl));

	tt = CDTIME_T_TO_TIME_T (vl->time);
	switch (ds->ds[0].type)
	{
		case DS_TYPE_DERIVE:
			status = ssnprintf (buffer, buffer_len, "%u:%"PRIi64,
				(unsigned) tt, vl->values[0].derive);
			break;
		case DS_TYPE_GAUGE:
			status = ssnprintf (buffer, buffer_len, "%u:"GAUGE_FORMAT,
				(unsigned) tt, vl->values[0].gauge);
			break;
		case DS_TYPE_COUNTER:
			status = ssnprintf (buffer, buffer_len, "%u:%llu",
				(unsigned) tt, vl->values[0].counter);
			break;
		case DS_TYPE_ABSOLUTE:
			status = ssnprintf (buffer, buffer_len, "%u:%"PRIu64,
				(unsigned) tt, vl->values[0].absolute);
			break;
		default:
			return (EINVAL);
	}

	if ((status < 1) || (status >= buffer_len))
		return (ENOMEM);

	return (0);
}