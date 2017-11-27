static int cna_query_volume_perf (host_config_t *host) /* {{{ */
{
	na_elem_t *data;
	int status;
	time_t now;

	if (host == NULL)
		return (EINVAL);

	/* If the user did not configure volume performance statistics, return
	 * without doing anything. */
	if (host->cfg_volume_perf == NULL)
		return (0);

	now = time (NULL);
	if ((host->cfg_volume_perf->interval.interval + host->cfg_volume_perf->interval.last_read) > now)
		return (0);

	status = cna_setup_volume_perf (host->cfg_volume_perf);
	if (status != 0)
		return (status);
	assert (host->cfg_volume_perf->query != NULL);

	data = na_server_invoke_elem (host->srv, host->cfg_volume_perf->query);
	if (na_results_status (data) != NA_OK)
	{
		ERROR ("netapp plugin: cna_query_volume_perf: na_server_invoke_elem failed for host %s: %s",
				host->name, na_results_reason (data));
		na_elem_free (data);
		return (-1);
	}

	status = cna_handle_volume_perf_data (host->name, host->cfg_volume_perf, data, host->interval);

	if (status == 0)
		host->cfg_volume_perf->interval.last_read = now;

	na_elem_free (data);
	return (status);
}