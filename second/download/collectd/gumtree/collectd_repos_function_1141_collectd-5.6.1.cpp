static int cna_register_host (host_config_t *host) /* {{{ */
{
	char cb_name[256];

	if (host->vfiler)
		ssnprintf (cb_name, sizeof (cb_name), "netapp-%s-%s",
				host->name, host->vfiler);
	else
		ssnprintf (cb_name, sizeof (cb_name), "netapp-%s", host->name);

	user_data_t ud = {
		.data = host,
		.free_func = (void (*) (void *)) free_host_config
	};

	plugin_register_complex_read (/* group = */ NULL, cb_name,
			/* callback  = */ cna_read,
			/* interval  = */ host->interval,
			/* user data = */ &ud);

	return (0);
}