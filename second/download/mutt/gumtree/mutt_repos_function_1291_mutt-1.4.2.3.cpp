void imap_logout_all (void) 
{
  CONNECTION* conn;
  CONNECTION* tmp;

  conn = mutt_socket_head ();

  while (conn)
  {
    tmp = conn->next;

    if (conn->account.type == M_ACCT_TYPE_IMAP && conn->fd >= 0)
    {
      mutt_message (_("Closing connection to %s..."), conn->account.host);
      imap_logout ((IMAP_DATA*) conn->data);
      mutt_clear_error ();
      mutt_socket_close (conn);
      mutt_socket_free (conn);
    }

    conn = tmp;
  }
}