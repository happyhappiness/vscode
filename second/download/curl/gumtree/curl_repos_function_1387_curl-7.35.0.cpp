void Curl_multi_set_easy_connection(struct SessionHandle *handle,
                                    struct connectdata *conn)
{
  handle->easy_conn = conn;
}