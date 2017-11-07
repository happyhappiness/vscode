IMAP_DATA* imap_conn_find (const ACCOUNT* account, int flags)
{
  CONNECTION* conn;
  IMAP_DATA* idata;
  ACCOUNT* creds;

  if (!(conn = mutt_conn_find (NULL, account)))
    return NULL;

  /* if opening a new UNSELECTED connection, preserve existing creds */
  creds = &(conn->account);

  /* make sure this connection is not in SELECTED state, if neccessary */
  if (flags & M_IMAP_CONN_NOSELECT)
    while (conn->data && ((IMAP_DATA*) conn->data)->state == IMAP_SELECTED)
    {
      if (!(conn = mutt_conn_find (conn, account)))
	return NULL;
      memcpy (&(conn->account), creds, sizeof (ACCOUNT));
    }
  
  idata = (IMAP_DATA*) conn->data;

  /* don't open a new connection if one isn't wanted */
  if (flags & M_IMAP_CONN_NONEW)
    if (!idata || idata->state == IMAP_DISCONNECTED)
      goto err_conn;
  
  if (!idata)
  {
    /* The current connection is a new connection */
    if (! (idata = imap_new_idata ()))
      goto err_conn;

    conn->data = idata;
    idata->conn = conn;
  }
  if (idata->state == IMAP_DISCONNECTED)
    if (imap_open_connection (idata) != 0)
      goto err_idata;
  
  return idata;

 err_idata:
  imap_free_idata (&idata);
 err_conn:
  mutt_socket_free (conn);

  return NULL;
}