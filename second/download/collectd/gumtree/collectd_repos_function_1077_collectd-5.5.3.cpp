static int cna_query_snapvault (host_config_t *host) /* {{{ */
{
	na_elem_t *data;
	int status;
	cdtime_t now;

	if (host == NULL)
		return EINVAL;

	if (host->cfg_snapvault == NULL)
		return 0;

	now = cdtime ();
	if ((host->cfg_snapvault->interval.interval + host->cfg_snapvault->interval.last_read) > now)
		return (0);

	status = cna_setup_snapvault (host->cfg_snapvault);
	if (status != 0)
		return (status);
	assert (host->cfg_snapvault->query != NULL);

	data = na_server_invoke_elem (host->srv, host->cfg_snapvault->query);
	if (na_results_status (data) != NA_OK)
	{
		ERROR ("netapp plugin: cna_query_snapvault: na_server_invoke_elem failed for host %s: %s",
				host->name, na_results_reason (data));
		na_elem_free (data);
		return (-1);
	}

	status = cna_handle_snapvault_iter (host, data);

	if (status == 0)
		host->cfg_snapvault->interval.last_read = now;

	na_elem_free (data);
	return (status);
}