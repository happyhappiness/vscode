void Curl_multi_handlePipeBreak(struct SessionHandle *data)
{
  data->easy_conn = NULL;
}