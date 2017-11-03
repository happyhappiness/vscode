CONNECTION* mutt_conn_find (const CONNECTION* start, const ACCOUNT* account)
{
  CONNECTION* conn;
  ciss_url_t url;
  char hook[LONG_STRING];

  /* account isn't actually modified, since url isn't either */
  mutt_account_tourl ((ACCOUNT*) account, &url);
  url.path = NULL;
  url_ciss_tostring (&url, hook, sizeof (hook), 0);
  mutt_account_hook (hook);

  conn = start ? start->next : Connections;
  while (conn)
  {
    if (mutt_account_match (account, &(conn->account)))
      return conn;
    conn = conn->next;
  }

  conn = socket_new_conn ();
  memcpy (&conn->account, account, sizeof (ACCOUNT));

  conn->next = Connections;
  Connections = conn;

  if (Tunnel && *Tunnel)
    mutt_tunnel_socket_setup (conn);
  else if (account->flags & MUTT_ACCT_SSL) 
  {
#if defined(USE_SSL)
    if (mutt_ssl_socket_setup (conn) < 0)
    {
      mutt_socket_free (conn);
      return NULL;
    }
#else
    mutt_error _("SSL is unavailable.");
    mutt_sleep (2);
    mutt_socket_free (conn);

    return NULL;
#endif
  }
  else
  {
    conn->conn_read = raw_socket_read;
    conn->conn_write = raw_socket_write;
    conn->conn_open = raw_socket_open;
    conn->conn_close = raw_socket_close;
    conn->conn_poll = raw_socket_poll;
  }

  return conn;
}