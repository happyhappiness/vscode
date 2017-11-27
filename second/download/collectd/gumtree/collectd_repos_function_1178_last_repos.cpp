static int cna_init_host(host_config_t *host) /* {{{ */
{
  /* Request version 1.1 of the ONTAP API */
  int major_version = 1, minor_version = 1;

  if (host == NULL)
    return EINVAL;

  if (host->srv != NULL)
    return 0;

  if (host->vfiler != NULL) /* Request version 1.7 of the ONTAP API */
    minor_version = 7;

  host->srv = na_server_open(host->host, major_version, minor_version);
  if (host->srv == NULL) {
    ERROR("netapp plugin: na_server_open (%s) failed.", host->host);
    return -1;
  }

  na_server_set_transport_type(host->srv, host->protocol,
                               /* transportarg = */ NULL);
  na_server_set_port(host->srv, host->port);
  na_server_style(host->srv, NA_STYLE_LOGIN_PASSWORD);
  na_server_adminuser(host->srv, host->username, host->password);
  na_server_set_timeout(host->srv, 5 /* seconds */);

  if (host->vfiler != NULL) {
    if (!na_server_set_vfiler(host->srv, host->vfiler)) {
      ERROR("netapp plugin: Failed to connect to VFiler '%s' on host '%s'.",
            host->vfiler, host->host);
      return -1;
    } else {
      INFO("netapp plugin: Connected to VFiler '%s' on host '%s'.",
           host->vfiler, host->host);
    }
  }

  return 0;
}