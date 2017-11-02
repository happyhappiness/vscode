static CURLcode
schannel_connect_step3(struct connectdata *conn, int sockindex)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  struct curl_schannel_cred *old_cred = NULL;
  bool incache;

  DEBUGASSERT(ssl_connect_3 == connssl->connecting_state);

  infof(data, "schannel: SSL/TLS connection with %s port %hu (step 3/3)\n",
        conn->host.name, conn->remote_port);

  if(!connssl->cred)
    return CURLE_SSL_CONNECT_ERROR;

  /* check if the required context attributes are met */
  if(connssl->ret_flags != connssl->req_flags) {
    if(!(connssl->ret_flags & ISC_RET_SEQUENCE_DETECT))
      failf(data, "schannel: failed to setup sequence detection");
    if(!(connssl->ret_flags & ISC_RET_REPLAY_DETECT))
      failf(data, "schannel: failed to setup replay detection");
    if(!(connssl->ret_flags & ISC_RET_CONFIDENTIALITY))
      failf(data, "schannel: failed to setup confidentiality");
    if(!(connssl->ret_flags & ISC_RET_ALLOCATED_MEMORY))
      failf(data, "schannel: failed to setup memory allocation");
    if(!(connssl->ret_flags & ISC_RET_STREAM))
      failf(data, "schannel: failed to setup stream orientation");
    return CURLE_SSL_CONNECT_ERROR;
  }

  /* increment the reference counter of the credential/session handle */
  if(connssl->cred && connssl->ctxt) {
    connssl->cred->refcount++;
    infof(data, "schannel: incremented credential handle refcount = %d\n",
          connssl->cred->refcount);
  }

  /* save the current session data for possible re-use */
  incache = !(Curl_ssl_getsessionid(conn, (void **)&old_cred, NULL));
  if(incache) {
    if(old_cred != connssl->cred) {
      infof(data, "schannel: old credential handle is stale, removing\n");
      Curl_ssl_delsessionid(conn, (void *)old_cred);
      incache = FALSE;
    }
  }

  if(!incache) {
    result = Curl_ssl_addsessionid(conn, (void *)connssl->cred,
                                   sizeof(struct curl_schannel_cred));
    if(result) {
      failf(data, "schannel: failed to store credential handle");
      return result;
    }
    else {
      connssl->cred->cached = TRUE;
      infof(data, "schannel: stored credential handle in session cache\n");
    }
  }

  connssl->connecting_state = ssl_connect_done;

  return CURLE_OK;
}