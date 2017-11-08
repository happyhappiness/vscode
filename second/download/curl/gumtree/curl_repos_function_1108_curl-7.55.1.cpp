CURLcode Curl_input_ntlm(struct connectdata *conn,
                         bool proxy,         /* if proxy or not */
                         const char *header) /* rest of the www-authenticate:
                                                header */
{
  /* point to the correct struct with this */
  struct ntlmdata *ntlm;
  CURLcode result = CURLE_OK;

  ntlm = proxy ? &conn->proxyntlm : &conn->ntlm;

  if(checkprefix("NTLM", header)) {
    header += strlen("NTLM");

    while(*header && ISSPACE(*header))
      header++;

    if(*header) {
      result = Curl_auth_decode_ntlm_type2_message(conn->data, header, ntlm);
      if(result)
        return result;

      ntlm->state = NTLMSTATE_TYPE2; /* We got a type-2 message */
    }
    else {
      if(ntlm->state == NTLMSTATE_LAST) {
        infof(conn->data, "NTLM auth restarted\n");
        Curl_http_ntlm_cleanup(conn);
      }
      else if(ntlm->state == NTLMSTATE_TYPE3) {
        infof(conn->data, "NTLM handshake rejected\n");
        Curl_http_ntlm_cleanup(conn);
        ntlm->state = NTLMSTATE_NONE;
        return CURLE_REMOTE_ACCESS_DENIED;
      }
      else if(ntlm->state >= NTLMSTATE_TYPE1) {
        infof(conn->data, "NTLM handshake failure (internal error)\n");
        return CURLE_REMOTE_ACCESS_DENIED;
      }

      ntlm->state = NTLMSTATE_TYPE1; /* We should send away a type-1 */
    }
  }

  return result;
}