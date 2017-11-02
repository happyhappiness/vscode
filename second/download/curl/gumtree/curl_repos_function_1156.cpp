void Curl_resolver_cancel(struct connectdata *conn)
{
  destroy_async_data(&conn->async);
}