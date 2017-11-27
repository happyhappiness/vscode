static int cna_handle_snapvault_data (const char *hostname, /* {{{ */
		cfg_snapvault_t *cfg_snapvault, na_elem_t *data, cdtime_t interval)
{
	na_elem_iter_t status_iter;

	status = na_elem_child (data, "status-list");
	if (! status) {
		ERROR ("netapp plugin: SnapVault status record missing status-list");
		return (0);
	}

	status_iter = na_child_iterator (status);
	for (na_elem_t *status = na_iterator_next (&status_iter);
			status != NULL;
			status = na_iterator_next (&status_iter))
	{
		const char *dest_sys, *dest_path, *src_sys, *src_path;
		char plugin_instance[DATA_MAX_NAME_LEN];
		uint64_t value;

		dest_sys  = na_child_get_string (status, "destination-system");
		dest_path = na_child_get_string (status, "destination-path");
		src_sys   = na_child_get_string (status, "source-system");
		src_path  = na_child_get_string (status, "source-path");

		if ((! dest_sys) || (! dest_path) || (! src_sys) || (! src_path))
			continue;

		value = na_child_get_uint64 (status, "lag-time", UINT64_MAX);
		if (value == UINT64_MAX) /* no successful baseline transfer yet */
			continue;

		/* possible TODO: make plugin instance configurable */
		ssnprintf (plugin_instance, sizeof (plugin_instance),
				"snapvault-%s", dest_path);
		submit_double (hostname, plugin_instance, /* type = */ "delay", NULL,
				(double)value, /* timestamp = */ 0, interval);

		value = na_child_get_uint64 (status, "last-transfer-duration", UINT64_MAX);
		if (value != UINT64_MAX)
			submit_double (hostname, plugin_instance, /* type = */ "duration", "last_transfer",
					(double)value, /* timestamp = */ 0, interval);

		value = na_child_get_uint64 (status, "transfer-progress", UINT64_MAX);
		if (value == UINT64_MAX)
			value = na_child_get_uint64 (status, "last-transfer-size", UINT64_MAX);
		if (value != UINT64_MAX) {
			value *= 1024; /* this is kilobytes */
			submit_derive (hostname, plugin_instance, /* type = */ "if_rx_octets", "transferred",
					value, /* timestamp = */ 0, interval);
		}
	} /* for (status) */

	return (0);
}