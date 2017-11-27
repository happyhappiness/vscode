static int pplugin_dispatch_values (pTHX_ HV *values)
{
	value_list_t list = VALUE_LIST_INIT;
	value_t      *val = NULL;

	SV **tmp = NULL;

	int ret = 0;

	if (NULL == values)
		return -1;

	if (NULL == (tmp = hv_fetch (values, "type", 4, 0))) {
		log_err ("pplugin_dispatch_values: No type given.");
		return -1;
	}

	sstrncpy (list.type, SvPV_nolen (*tmp), sizeof (list.type));

	if ((NULL == (tmp = hv_fetch (values, "values", 6, 0)))
			|| (! (SvROK (*tmp) && (SVt_PVAV == SvTYPE (SvRV (*tmp)))))) {
		log_err ("pplugin_dispatch_values: No valid values given.");
		return -1;
	}

	{
		AV  *array = (AV *)SvRV (*tmp);
		int len    = av_len (array) + 1;

		if (len <= 0)
			return -1;

		val = (value_t *)smalloc (len * sizeof (value_t));

		list.values_len = av2value (aTHX_ list.type, (AV *)SvRV (*tmp),
				val, len);
		list.values = val;

		if (-1 == list.values_len) {
			sfree (val);
			return -1;
		}
	}

	if (NULL != (tmp = hv_fetch (values, "time", 4, 0))) {
		list.time = (time_t)SvIV (*tmp);
	}
	else {
		list.time = time (NULL);
	}

	if (NULL != (tmp = hv_fetch (values, "host", 4, 0))) {
		sstrncpy (list.host, SvPV_nolen (*tmp), sizeof (list.host));
	}
	else {
		sstrncpy (list.host, hostname_g, sizeof (list.host));
	}

	if (NULL != (tmp = hv_fetch (values, "plugin", 6, 0)))
		sstrncpy (list.plugin, SvPV_nolen (*tmp), sizeof (list.plugin));

	if (NULL != (tmp = hv_fetch (values, "plugin_instance", 15, 0)))
		sstrncpy (list.plugin_instance, SvPV_nolen (*tmp),
				sizeof (list.plugin_instance));

	if (NULL != (tmp = hv_fetch (values, "type_instance", 13, 0)))
		sstrncpy (list.type_instance, SvPV_nolen (*tmp),
				sizeof (list.type_instance));

	ret = plugin_dispatch_values (&list);

	sfree (val);
	return ret;
}