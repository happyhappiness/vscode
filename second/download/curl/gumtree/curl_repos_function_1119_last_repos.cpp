void Curl_http2_cleanup_dependencies(struct Curl_easy *data)
{
  while(data->set.stream_dependents) {
    struct Curl_easy *tmp = data->set.stream_dependents->data;
    Curl_http2_remove_child(data, tmp);
    if(data->set.stream_depends_on)
      Curl_http2_add_child(data->set.stream_depends_on, tmp, FALSE);
  }

  if(data->set.stream_depends_on)
    Curl_http2_remove_child(data->set.stream_depends_on, data);
}