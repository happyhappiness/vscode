void Curl_multi_handlePipeBreak(struct SessionHandle *data)
{
  struct Curl_one_easy *one_easy = data->set.one_easy;

  if(one_easy)
    one_easy->easy_conn = NULL;
}