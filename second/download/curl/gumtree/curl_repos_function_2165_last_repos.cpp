void Curl_pp_init(struct pingpong *pp)
{
  struct connectdata *conn = pp->conn;
  pp->nread_resp = 0;
  pp->linestart_resp = conn->data->state.buffer;
  pp->pending_resp = TRUE;
  pp->response = Curl_tvnow(); /* start response time-out now! */
}