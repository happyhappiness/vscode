static int cna_handle_quota_data (const host_config_t *host, /* {{{ */
		cfg_quota_t *cfg_quota, na_elem_t *data)
{
	na_elem_t *elem_quota;
	na_elem_t *elem_quotas;
	na_elem_iter_t iter_quota;

	elem_quotas = na_elem_child (data, "quotas");
	if (elem_quotas == NULL)
	{
		ERROR ("netapp plugin: cna_handle_quota_data: "
				"na_elem_child (\"quotas\") failed "
				"for host %s.", host->name);
		return (-1);
	}

	iter_quota = na_child_iterator (elem_quotas);
	for (elem_quota = na_iterator_next (&iter_quota);
			elem_quota != NULL;
			elem_quota = na_iterator_next (&iter_quota))
	{
		const char *quota_type, *volume_name, *tree_name;
		uint64_t value;

		char plugin_instance[DATA_MAX_NAME_LEN];

		quota_type = na_child_get_string (elem_quota, "quota-type");
		if (quota_type == NULL)
			continue;

		/* possible TODO: support other types as well */
		if (strcmp (quota_type, "tree") != 0)
			continue;

		tree_name = na_child_get_string (elem_quota, "tree");
		if ((tree_name == NULL) || (*tree_name == '\0'))
			continue;

		volume_name = na_child_get_string (elem_quota, "volume");
		if (volume_name == NULL)
			continue;

		ssnprintf (plugin_instance, sizeof (plugin_instance),
				"quota-%s-%s", volume_name, tree_name);

		value = na_child_get_uint64 (elem_quota, "disk-used", UINT64_MAX);
		if (value != UINT64_MAX) {
			value *= 1024; /* disk-used reports kilobytes */
			submit_double (host->name, plugin_instance,
					/* type = */ "df_complex", /* type instance = */ NULL,
					(double)value, /* timestamp = */ 0,
					host->cfg_quota->interval.interval);
		}

		value = na_child_get_uint64 (elem_quota, "files-used", UINT64_MAX);
		if (value != UINT64_MAX) {
			submit_double (host->name, plugin_instance,
					/* type = */ "files", /* type instance = */ NULL,
					(double)value, /* timestamp = */ 0,
					host->cfg_quota->interval.interval);
		}
	} /* for (elem_quota) */

	return (0);
}