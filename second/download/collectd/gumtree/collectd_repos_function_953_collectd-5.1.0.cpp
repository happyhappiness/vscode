static int cna_read (user_data_t *ud) { /* {{{ */
	host_config_t *host;
	int status;

	if ((ud == NULL) || (ud->data == NULL))
		return (-1);

	host = ud->data;

	status = cna_init_host (host);
	if (status != 0)
		return (status);
	
	cna_query_wafl (host);
	cna_query_disk (host);
	cna_query_volume_perf (host);
	cna_query_volume_usage (host);
	cna_query_system (host);

	return 0;
}