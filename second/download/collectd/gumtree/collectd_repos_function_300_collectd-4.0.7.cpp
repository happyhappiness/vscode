static int value_list2hv (value_list_t *vl, data_set_t *ds, HV *hash)
{
	AV *values = NULL;

	int i   = 0;
	int len = 0;

	if ((NULL == vl) || (NULL == ds) || (NULL == hash))
		return -1;

	len = vl->values_len;

	if (ds->ds_num < len) {
		log_warn ("value2av: Value length exceeds data set length.");
		len = ds->ds_num;
	}

	values = Perl_newAV (perl);
	Perl_av_extend (perl, values, len - 1);

	for (i = 0; i < len; ++i) {
		SV *val = NULL;

		if (DS_TYPE_COUNTER == ds->ds[i].type)
			val = Perl_newSViv (perl, vl->values[i].counter);
		else
			val = Perl_newSVnv (perl, vl->values[i].gauge);

		if (NULL == Perl_av_store (perl, values, i, val)) {
			Perl_av_undef (perl, values);
			return -1;
		}
	}

	if (NULL == Perl_hv_store (perl, hash, "values", 6,
			Perl_newRV_noinc (perl, (SV *)values), 0))
		return -1;

	if (0 != vl->time)
		if (NULL == Perl_hv_store (perl, hash, "time", 4,
				Perl_newSViv (perl, vl->time), 0))
			return -1;

	if ('\0' != vl->host[0])
		if (NULL == Perl_hv_store (perl, hash, "host", 4,
				Perl_newSVpv (perl, vl->host, 0), 0))
			return -1;

	if ('\0' != vl->plugin[0])
		if (NULL == Perl_hv_store (perl, hash, "plugin", 6,
				Perl_newSVpv (perl, vl->plugin, 0), 0))
			return -1;

	if ('\0' != vl->plugin_instance[0])
		if (NULL == Perl_hv_store (perl, hash, "plugin_instance", 15,
				Perl_newSVpv (perl, vl->plugin_instance, 0), 0))
			return -1;

	if ('\0' != vl->type_instance[0])
		if (NULL == Perl_hv_store (perl, hash, "type_instance", 13,
				Perl_newSVpv (perl, vl->type_instance, 0), 0))
			return -1;
	return 0;
}