CURLcode http_close(struct connectdata *conn)
{
  if(conn->data->auth_host)
    free(conn->data->auth_host);
  return CURLE_OK;
}