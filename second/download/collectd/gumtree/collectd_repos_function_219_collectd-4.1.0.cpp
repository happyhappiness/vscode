static void csnmp_host_close_session (host_definition_t *host)
{
  int status;

  if (host->sess_handle == NULL)
    return;

  status = snmp_sess_close (host->sess_handle);

  if (status != 0)
  {
    char *errstr = NULL;

    snmp_sess_error (host->sess_handle, NULL, NULL, &errstr);

    ERROR ("snmp plugin: snmp_sess_close failed: %s",
	(errstr == NULL) ? "Unknown problem" : errstr);
    sfree (errstr);
  }

  host->sess_handle = NULL;
}