static void state(struct connectdata *conn, imapstate newstate)
{
  struct imap_conn *imapc = &conn->proto.imapc;
#if defined(DEBUGBUILD) && !defined(CURL_DISABLE_VERBOSE_STRINGS)
  /* for debug purposes */
  static const char * const names[]={
    "STOP",
    "SERVERGREET",
    "CAPABILITY",
    "STARTTLS",
    "UPGRADETLS",
    "AUTHENTICATE_PLAIN",
    "AUTHENTICATE_LOGIN",
    "AUTHENTICATE_LOGIN_PASSWD",
    "AUTHENTICATE_CRAMMD5",
    "AUTHENTICATE_DIGESTMD5",
    "AUTHENTICATE_DIGESTMD5_RESP",
    "AUTHENTICATE_NTLM",
    "AUTHENTICATE_NTLM_TYPE2MSG",
    "AUTHENTICATE_XOAUTH2",
    "AUTHENTICATE_CANCEL",
    "AUTHENTICATE_FINAL",
    "LOGIN",
    "LIST",
    "SELECT",
    "FETCH",
    "FETCH_FINAL",
    "APPEND",
    "APPEND_FINAL",
    "LOGOUT",
    /* LAST */
  };

  if(imapc->state != newstate)
    infof(conn->data, "IMAP %p state change from %s to %s\n",
          (void *)imapc, names[imapc->state], names[newstate]);
#endif

  imapc->state = newstate;
}