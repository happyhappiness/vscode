static int pplugin_dispatch_values (char *name, HV *values)
{
	value_list_t list = VALUE_LIST_INIT;
	value_t      *val = NULL;

	SV **tmp = NULL;

	int ret = 0;

	if ((NULL == name) || (NULL == values))
		return -1;

	if ((NULL == (tmp = Perl_hv_fetch (perl, values, "values", 6, 0)))
			|| (! (SvROK (*tmp) && (SVt_PVAV == SvTYPE (SvRV (*tmp)))))) {
		log_err ("pplugin_dispatch_values: No valid values given.");
		return -1;
	}

	{
		AV  *array = (AV *)SvRV (*tmp);
		int len    = Perl_av_len (perl, array) + 1;

		val = (value_t *)smalloc (len * sizeof (value_t));

		list.values_len = av2value (name, (AV *)SvRV (*tmp), val, len);
		list.values = val;

		if (-1 == list.values_len) {
			sfree (val);
			return -1;
		}
	}

	if (NULL != (tmp = Perl_hv_fetch (perl, values, "time", 4, 0))) {
		list.time = (time_t)SvIV (*tmp);
	}
	else {
		list.time = time (NULL);
	}

	if (NULL != (tmp = Perl_hv_fetch (perl, values, "host", 4, 0))) {
		strncpy (list.host, SvPV_nolen (*tmp), DATA_MAX_NAME_LEN);
		list.host[DATA_MAX_NAME_LEN - 1] = '\0';
	}
	else {
		strcpy (list.host, hostname_g);
	}

	if (NULL != (tmp = Perl_hv_fetch (perl, values, "plugin", 6, 0))) {
		strncpy (list.plugin, SvPV_nolen (*tmp), DATA_MAX_NAME_LEN);
		list.plugin[DATA_MAX_NAME_LEN - 1] = '\0';
	}

	if (NULL != (tmp = Perl_hv_fetch (perl, values,
			"plugin_instance", 15, 0))) {
		strncpy (list.plugin_instance, SvPV_nolen (*tmp), DATA_MAX_NAME_LEN);
		list.plugin_instance[DATA_MAX_NAME_LEN - 1] = '\0';
	}

	if (NULL != (tmp = Perl_hv_fetch (perl, values, "type_instance", 13, 0))) {
		strncpy (list.type_instance, SvPV_nolen (*tmp), DATA_MAX_NAME_LEN);
		list.type_instance[DATA_MAX_NAME_LEN - 1] = '\0';
	}

	ret = plugin_dispatch_values (name, &list);

	sfree (val);
	return ret;
}