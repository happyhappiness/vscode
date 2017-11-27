static int av2data_set (pTHX_ AV *array, char *name, data_set_t *ds)
{
	int len;

	if ((NULL == array) || (NULL == name) || (NULL == ds))
		return -1;

	len = av_len (array);

	if (-1 == len) {
		log_err ("av2data_set: Invalid data set.");
		return -1;
	}

	ds->ds = smalloc ((len + 1) * sizeof (*ds->ds));
	ds->ds_num = len + 1;

	for (int i = 0; i <= len; ++i) {
		SV **elem = av_fetch (array, i, 0);

		if (NULL == elem) {
			log_err ("av2data_set: Failed to fetch data source %i.", i);
			return -1;
		}

		if (! (SvROK (*elem) && (SVt_PVHV == SvTYPE (SvRV (*elem))))) {
			log_err ("av2data_set: Invalid data source.");
			return -1;
		}

		if (-1 == hv2data_source (aTHX_ (HV *)SvRV (*elem), &ds->ds[i]))
			return -1;

		log_debug ("av2data_set: "
				"DS.name = \"%s\", DS.type = %i, DS.min = %f, DS.max = %f",
				ds->ds[i].name, ds->ds[i].type, ds->ds[i].min, ds->ds[i].max);
	}

	sstrncpy (ds->type, name, sizeof (ds->type));
	return 0;
}