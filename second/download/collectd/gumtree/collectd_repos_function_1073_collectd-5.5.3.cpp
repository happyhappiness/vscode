static int cna_query_quota (host_config_t *host) /* {{{ */
{
	na_elem_t *data;
	int status;
	cdtime_t now;

	if (host == NULL)
		return (EINVAL);

	/* If the user did not configure quota statistics, return without
	 * doing anything. */
	if (host->cfg_quota == NULL)
		return (0);

	now = cdtime ();
	if ((host->cfg_quota->interval.interval + host->cfg_quota->interval.last_read) > now)
		return (0);

	status = cna_setup_quota (host->cfg_quota);
	if (status != 0)
		return (status);
	assert (host->cfg_quota->query != NULL);

	data = na_server_invoke_elem (host->srv, host->cfg_quota->query);
	if (na_results_status (data) != NA_OK)
	{
		ERROR ("netapp plugin: cna_query_quota: na_server_invoke_elem failed for host %s: %s",
				host->name, na_results_reason (data));
		na_elem_free (data);
		return (-1);
	}

	status = cna_handle_quota_data (host, host->cfg_quota, data);

	if (status == 0)
		host->cfg_quota->interval.last_read = now;

	na_elem_free (data);
	return (status);
}