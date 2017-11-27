static int av2value (pTHX_ char *name, AV *array, value_t *value, int len)
{
	const data_set_t *ds;

	int i = 0;

	if ((NULL == name) || (NULL == array) || (NULL == value))
		return -1;

	if (av_len (array) < len - 1)
		len = av_len (array) + 1;

	if (0 >= len)
		return -1;

	ds = plugin_get_ds (name);
	if (NULL == ds) {
		log_err ("av2value: Unknown dataset \"%s\"", name);
		return -1;
	}

	if (ds->ds_num < len) {
		log_warn ("av2value: Value length exceeds data set length.");
		len = ds->ds_num;
	}

	for (i = 0; i < len; ++i) {
		SV **tmp = av_fetch (array, i, 0);

		if (NULL != tmp) {
			if (DS_TYPE_COUNTER == ds->ds[i].type)
				value[i].counter = SvIV (*tmp);
			else
				value[i].gauge = SvNV (*tmp);
		}
		else {
			return -1;
		}
	}
	return len;
}