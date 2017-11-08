void Curl_speedinit(struct Curl_easy *data)
{
  memset(&data->state.keeps_speed, 0, sizeof(struct curltime));
}