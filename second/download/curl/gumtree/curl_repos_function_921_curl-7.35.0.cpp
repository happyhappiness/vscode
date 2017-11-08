void Curl_cleanup_negotiate(struct SessionHandle *data)
{
  cleanup(&data->state.negotiate);
  cleanup(&data->state.proxyneg);
}