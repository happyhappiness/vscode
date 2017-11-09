static CURLcode pop3_parse_url_path(struct connectdata *conn)
{
  /* The POP3 struct is already initialised in pop3_connect() */
  struct Curl_easy *data = conn->data;
  struct POP3 *pop3 = data->req.protop;
  const char *path = data->state.path;

  /* URL decode the path for the message ID */
  return Curl_urldecode(data, path, 0, &pop3->id, NULL, TRUE);
}