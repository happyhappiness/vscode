static int av2value (char *name, AV *array, value_t *value, int len)
{
	SV **tmp = NULL;

	ds_types_t *ds = NULL;

	int i = 0;

	if ((NULL == name) || (NULL == array) || (NULL == value))
		return -1;

	if (Perl_av_len (perl, array) < len - 1)
		len = Perl_av_len (perl, array) + 1;

	if (0 >= len)
		return -1;

	tmp = Perl_hv_fetch (perl, data_sets, name, strlen (name), 0);
	if (NULL == tmp) {
		log_err ("av2value: No dataset for \"%s\".", name);
		return -1;
	}
	ds = (ds_types_t *)SvIV ((SV *)SvRV (*tmp));

	if (ds->len < len) {
		log_warn ("av2value: Value length exceeds data set length.");
		len = ds->len;
	}

	for (i = 0; i < len; ++i) {
		SV **tmp = Perl_av_fetch (perl, array, i, 0);

		if (NULL != tmp) {
			if (DS_TYPE_COUNTER == ds->values[i])
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