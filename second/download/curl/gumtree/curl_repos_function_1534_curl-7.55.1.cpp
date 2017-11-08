static CURLcode smb_disconnect(struct connectdata *conn, bool dead)
{
  struct smb_conn *smbc = &conn->proto.smbc;
  struct smb_request *req = conn->data->req.protop;

  (void) dead;

  Curl_safefree(smbc->domain);
  Curl_safefree(smbc->recv_buf);

  /* smb_done is not always called, so cleanup the request */
  if(req) {
    Curl_safefree(req->share);
  }

  return CURLE_OK;
}