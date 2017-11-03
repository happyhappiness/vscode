static bool complete_request(struct connectdata *conn,
                             curl_off_t remaining_bytes)
{
#if defined(USE_NTLM) || defined(USE_SPNEGO)
  struct SessionHandle *data = conn->data;
  bool have_ntlm_or_negotiate = FALSE;
  bool auth_started = FALSE;

  /* don't reset connection when we're in NTLM or Negotiate authentication;
   * those authenticate the connection - creating a new connection breaks the
   * authentication.
   */

#if defined(USE_NTLM)
  /* proxy NTLM authentication */
  if((data->state.authproxy.picked == CURLAUTH_NTLM) ||
      (data->state.authproxy.picked == CURLAUTH_NTLM_WB)) {
    have_ntlm_or_negotiate = TRUE;
    auth_started = auth_started
                 || (conn->proxyntlm.state != NTLMSTATE_NONE);
  }

  /* normal NTLM authentication */
  if((data->state.authhost.picked == CURLAUTH_NTLM) ||
      (data->state.authhost.picked == CURLAUTH_NTLM_WB)) {
    have_ntlm_or_negotiate = TRUE;
    auth_started = auth_started
                 || (conn->ntlm.state != NTLMSTATE_NONE);
  }
#endif

#if defined(USE_SPNEGO)
  /* proxy Negotiate authentication */
  if(data->state.authproxy.picked == CURLAUTH_NEGOTIATE) {
    have_ntlm_or_negotiate = TRUE;
    auth_started = auth_started
                 || (data->state.proxyneg.state != GSS_AUTHNONE);
  }

  /* normal Negotiate authentication */
  if(data->state.authhost.picked == CURLAUTH_NEGOTIATE) {
    have_ntlm_or_negotiate = TRUE;
    auth_started = auth_started
                 || (data->state.negotiate.state != GSS_AUTHNONE);
  }
#endif

  if(have_ntlm_or_negotiate) {
    if(remaining_bytes < 2000 || auth_started) {
      /* NTLM/Negotiation has started *OR* there is just a little (<2K)
       * data left to send, keep on sending.
       */

      /* rewind data when completely done sending! */
      if(!conn->bits.authneg) {
        conn->bits.rewindaftersend = TRUE;
        infof(data, "Rewind stream after send\n");
      }

      return TRUE;
    }

    infof(data, "NTLM/Negotiate send, close instead of sending %"
          CURL_FORMAT_CURL_OFF_T " bytes\n",
          remaining_bytes);
  }
#else
  /* unused parameters: */
  (void)conn;
  (void)remaining_bytes;
#endif

  return FALSE;
}