struct curl_slist *Curl_none_engines_list(struct Curl_easy *data UNUSED_PARAM)
{
  (void)data;
  return (struct curl_slist *)NULL;
}