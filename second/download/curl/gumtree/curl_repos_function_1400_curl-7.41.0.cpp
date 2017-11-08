static void conn_state(struct connectdata *conn, enum smb_conn_state newstate)
{
  struct smb_conn *smb = &conn->proto.smbc;
#if defined(DEBUGBUILD) && !defined(CURL_DISABLE_VERBOSE_STRINGS)
  /* For debug purposes */
  static const char * const names[] = {
    "SMB_NOT_CONNECTED",
    "SMB_CONNECTING",
    "SMB_NEGOTIATE",
    "SMB_SETUP",
    "SMB_CONNECTED",
    /* LAST */
  };

  if(smb->state != newstate)
    infof(conn->data, "SMB conn %p state change from %s to %s\n",
    (void *)smb, names[smb->state], names[newstate]);
#endif

  smb->state = newstate;
}