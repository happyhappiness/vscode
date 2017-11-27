static int av2value (char *name, AV *array, value_t *value, int len)
{
	const data_set_t *ds;

	int i = 0;

	if ((NULL == name) || (NULL == array) || (NULL == value))
		return -1;

	if (Perl_av_len (perl, array) < len - 1)
		len = Perl_av_len (perl, array) + 1;

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
		SV **tmp = Perl_av_fetch (perl, array, i, 0);

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