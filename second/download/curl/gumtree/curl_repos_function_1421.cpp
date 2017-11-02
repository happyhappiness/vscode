static CURLcode smb_done(struct connectdata *conn, CURLcode status,
                         bool premature)
{
  struct smb_request *req = conn->data->req.protop;

  (void) premature;

  Curl_safefree(req->share);
  Curl_safefree(conn->data->req.protop);

  return status;
}