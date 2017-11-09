static CURLcode pop3_state_command_resp(struct connectdata *conn,
                                        int pop3code,
                                        pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct POP3 *pop3 = data->req.protop;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  struct pingpong *pp = &pop3c->pp;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    state(conn, POP3_STOP);
    return CURLE_RECV_ERROR;
  }

  /* This 'OK' line ends with a CR LF pair which is the two first bytes of the
     EOB string so count this is two matching bytes. This is necessary to make
     the code detect the EOB if the only data than comes now is %2e CR LF like
     when there is no body to return. */
  pop3c->eob = 2;

  /* But since this initial CR LF pair is not part of the actual body, we set
     the strip counter here so that these bytes won't be delivered. */
  pop3c->strip = 2;

  if(pop3->transfer == FTPTRANSFER_BODY) {
    /* POP3 download */
    Curl_setup_transfer(conn, FIRSTSOCKET, -1, FALSE, NULL, -1, NULL);

    if(pp->cache) {
      /* The header "cache" contains a bunch of data that is actually body
         content so send it as such. Note that there may even be additional
         "headers" after the body */

      if(!data->set.opt_no_body) {
        result = Curl_pop3_write(conn, pp->cache, pp->cache_size);
        if(result)
          return result;
      }

      /* Free the cache */
      Curl_safefree(pp->cache);

      /* Reset the cache size */
      pp->cache_size = 0;
    }
  }

  /* End of DO phase */
  state(conn, POP3_STOP);

  return result;
}