static int tls_set_priority(tlssockdata *data)
{
  size_t nproto = 4;
  char *priority;
  size_t priority_size;
  int err;

  priority_size = SHORT_STRING + mutt_strlen (SslCiphers);
  priority = safe_malloc (priority_size);

  priority[0] = 0;
  if (SslCiphers)
    safe_strcat (priority, priority_size, SslCiphers);
  else
    safe_strcat (priority, priority_size, "NORMAL");

  if (! option(OPTTLSV1_2))
  {
    nproto--;
    safe_strcat (priority, priority_size, ":-VERS-TLS1.2");
  }
  if (! option(OPTTLSV1_1))
  {
    nproto--;
    safe_strcat (priority, priority_size, ":-VERS-TLS1.1");
  }
  if (! option(OPTTLSV1))
  {
    nproto--;
    safe_strcat (priority, priority_size, ":-VERS-TLS1.0");
  }
  if (! option(OPTSSLV3))
  {
    nproto--;
    safe_strcat (priority, priority_size, ":-VERS-SSL3.0");
  }

  if (nproto == 0)
  {
    mutt_error (_("All available protocols for TLS/SSL connection disabled"));
    FREE (&priority);
    return -1;
  }

  if ((err = gnutls_priority_set_direct (data->state, priority, NULL)) < 0)
  {
    mutt_error ("gnutls_priority_set_direct(%s): %s", priority, gnutls_strerror(err));
    mutt_sleep (2);
    FREE (&priority);
    return -1;
  }

  FREE (&priority);
  return 0;
}