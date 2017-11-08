static CURLcode pop3_init(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct POP3 *pop3;

  pop3 = data->req.protop = calloc(sizeof(struct POP3), 1);
  if(!pop3)
    result = CURLE_OUT_OF_MEMORY;

  return result;
}