static int pplugin_register_data_set (char *name, AV *dataset)
{
	int len = -1;
	int i   = 0;

	data_source_t *ds  = NULL;
	data_set_t    *set = NULL;

	if ((NULL == name) || (NULL == dataset))
		return -1;

	len = Perl_av_len (perl, dataset);

	if (-1 == len)
		return -1;

	ds  = (data_source_t *)smalloc ((len + 1) * sizeof (data_source_t));
	set = (data_set_t *)smalloc (sizeof (data_set_t));

	for (i = 0; i <= len; ++i) {
		SV **elem = Perl_av_fetch (perl, dataset, i, 0);

		if (NULL == elem)
			return -1;

		if (! (SvROK (*elem) && (SVt_PVHV == SvTYPE (SvRV (*elem))))) {
			log_err ("pplugin_register_data_set: Invalid data source.");
			return -1;
		}

		if (-1 == hv2data_source ((HV *)SvRV (*elem), &ds[i]))
			return -1;

		log_debug ("pplugin_register_data_set: "
				"DS.name = \"%s\", DS.type = %i, DS.min = %f, DS.max = %f",
				ds[i].name, ds[i].type, ds[i].min, ds[i].max);
	}

	strncpy (set->type, name, DATA_MAX_NAME_LEN);
	set->type[DATA_MAX_NAME_LEN - 1] = '\0';

	set->ds_num = len + 1;
	set->ds = ds;
	return plugin_register_data_set (set);
}