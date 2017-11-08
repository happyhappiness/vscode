void Curl_connect_free(struct Curl_easy *data)
{
  struct connectdata *conn = data->easy_conn;
  struct http_connect_state *s = conn->connect_state;
  if(s) {
    free(s);
    conn->connect_state = NULL;
  }
}