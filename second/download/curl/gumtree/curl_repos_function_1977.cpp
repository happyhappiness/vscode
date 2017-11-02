static void state(struct SASL *sasl, struct connectdata *conn,
                  saslstate newstate)
{
#if defined(DEBUGBUILD) && !defined(CURL_DISABLE_VERBOSE_STRINGS)
  /* for debug purposes */
  static const char * const names[]={
    "STOP",
    "PLAIN",
    "LOGIN",
    "LOGIN_PASSWD",
    "EXTERNAL",
    "CRAMMD5",
    "DIGESTMD5",
    "DIGESTMD5_RESP",
    "NTLM",
    "NTLM_TYPE2MSG",
    "GSSAPI",
    "GSSAPI_TOKEN",
    "GSSAPI_NO_DATA",
    "XOAUTH2",
    "CANCEL",
    "FINAL",
    /* LAST */
  };

  if(sasl->state != newstate)
    infof(conn->data, "SASL %p state change from %s to %s\n",
          (void *)sasl, names[sasl->state], names[newstate]);
#else
  (void) conn;
#endif

  sasl->state = newstate;
}