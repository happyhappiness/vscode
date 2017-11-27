static int cna_handle_snapvault_iter (host_config_t *host, /* {{{ */
		na_elem_t *data)
{
	const char *tag;

	uint32_t records_count;

	records_count = na_child_get_uint32 (data, "records", UINT32_MAX);
	if (records_count == UINT32_MAX)
		return 0;

	tag = na_child_get_string (data, "tag");
	if (! tag)
		return 0;

	DEBUG ("netapp plugin: Iterating %u SV records (tag = %s)", records_count, tag);

	for (uint32_t i = 0; i < records_count; ++i) {
		na_elem_t *elem;

		elem = na_server_invoke (host->srv,
				"snapvault-secondary-relationship-status-list-iter-next",
				"maximum", "1", "tag", tag, NULL);

		if (na_results_status (elem) != NA_OK)
		{
			ERROR ("netapp plugin: cna_handle_snapvault_iter: "
					"na_server_invoke failed for host %s: %s",
					host->name, na_results_reason (data));
			na_elem_free (elem);
			return (-1);
		}

		cna_handle_snapvault_data (host->name, host->cfg_snapvault, elem,
				host->cfg_snapvault->interval.interval);
		na_elem_free (elem);
	}

	na_elem_free (na_server_invoke (host->srv,
			"snapvault-secondary-relationship-status-list-iter-end",
			"tag", tag, NULL));
	return (0);
}