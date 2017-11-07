int imap_close_connection (CONTEXT *ctx)
{
  dprint (1, (debugfile, "imap_close_connection(): closing connection\n"));
  /* if the server didn't shut down on us, close the connection gracefully */
  if (CTX_DATA->status != IMAP_BYE)
  {
    mutt_message _("Closing connection to IMAP server...");
    imap_logout (CTX_DATA);
    mutt_clear_error ();
  }
  mutt_socket_close (CTX_DATA->conn);
  CTX_DATA->state = IMAP_DISCONNECTED;
  CTX_DATA->conn->data = NULL;
  return 0;
}