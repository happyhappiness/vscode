void Curl_reset_reqproto(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;
  if(data->state.proto.generic && data->state.current_conn != conn) {
    free(data->state.proto.generic);
    data->state.proto.generic = NULL;
  }
  data->state.current_conn = conn;
}