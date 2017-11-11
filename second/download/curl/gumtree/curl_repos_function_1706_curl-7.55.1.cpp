void Curl_resolver_cancel(struct connectdata *conn)
{
  if(conn->data && conn->data->state.resolver)
    ares_cancel((ares_channel)conn->data->state.resolver);
  destroy_async_data(&conn->async);
}