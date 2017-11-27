static void csnmp_host_open_session (host_definition_t *host)
{
  struct snmp_session sess;

  if (host->sess_handle != NULL)
    csnmp_host_close_session (host);

  snmp_sess_init (&sess);
  sess.peername = host->address;
  sess.community = (u_char *) host->community;
  sess.community_len = strlen (host->community);
  sess.version = (host->version == 1) ? SNMP_VERSION_1 : SNMP_VERSION_2c;

  /* snmp_sess_open will copy the `struct snmp_session *'. */
  host->sess_handle = snmp_sess_open (&sess);

  if (host->sess_handle == NULL)
  {
    char *errstr = NULL;

    snmp_error (&sess, NULL, NULL, &errstr);

    ERROR ("snmp plugin: host %s: snmp_sess_open failed: %s",
        host->name, (errstr == NULL) ? "Unknown problem" : errstr);
    sfree (errstr);
  }
}