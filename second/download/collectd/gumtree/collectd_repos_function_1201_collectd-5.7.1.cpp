static int cna_read(user_data_t *ud) { /* {{{ */
  host_config_t *host;
  int status;

  if ((ud == NULL) || (ud->data == NULL))
    return (-1);

  host = ud->data;

  status = cna_init_host(host);
  if (status != 0)
    return (status);

  status = cna_read_internal(host);
  if (status != 0) {
    if (host->srv != NULL)
      na_server_close(host->srv);
    host->srv = NULL;
  }

  return 0;
}