static int cna_init_host (host_config_t *host) /* {{{ */
{
	if (host == NULL)
		return (EINVAL);

	if (host->srv != NULL)
		return (0);

	/* Request version 1.1 of the ONTAP API */
	host->srv = na_server_open(host->host,
			/* major version = */ 1, /* minor version = */ 1); 
	if (host->srv == NULL) {
		ERROR ("netapp plugin: na_server_open (%s) failed.", host->host);
		return (-1);
	}

	na_server_set_transport_type(host->srv, host->protocol,
			/* transportarg = */ NULL);
	na_server_set_port(host->srv, host->port);
	na_server_style(host->srv, NA_STYLE_LOGIN_PASSWORD);
	na_server_adminuser(host->srv, host->username, host->password);
	na_server_set_timeout(host->srv, 5 /* seconds */);

	return (0);
}