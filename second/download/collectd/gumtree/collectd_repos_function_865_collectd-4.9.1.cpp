static int cna_query_system (host_config_t *host) /* {{{ */
{
	na_elem_t *data;
	int status;
	time_t now;

	if (host == NULL)
		return (EINVAL);

	/* If system statistics were not configured, return without doing anything. */
	if (host->cfg_system == NULL)
		return (0);

	now = time (NULL);
	if ((host->cfg_system->interval.interval + host->cfg_system->interval.last_read) > now)
		return (0);

	status = cna_setup_system (host->cfg_system);
	if (status != 0)
		return (status);
	assert (host->cfg_system->query != NULL);

	data = na_server_invoke_elem(host->srv, host->cfg_system->query);
	if (na_results_status (data) != NA_OK)
	{
		ERROR ("netapp plugin: cna_query_system: na_server_invoke_elem failed for host %s: %s",
				host->name, na_results_reason (data));
		na_elem_free (data);
		return (-1);
	}

	status = cna_handle_system_data (host->name, host->cfg_system, data);

	if (status == 0)
		host->cfg_system->interval.last_read = now;

	na_elem_free (data);
	return (status);
}