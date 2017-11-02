void Curl_speedinit(struct SessionHandle *data)
{
  memset(&data->state.keeps_speed, 0, sizeof(struct timeval));
}