void Curl_http2_remove_child(struct Curl_easy *parent, struct Curl_easy *child)
{
  struct Curl_http2_dep *last = 0;
  struct Curl_http2_dep *data = parent->set.stream_dependents;
  DEBUGASSERT(child->set.stream_depends_on == parent);

  while(data && data->data != child) {
    last = data;
    data = data->next;
  }

  DEBUGASSERT(data);

  if(data) {
    if(last) {
      last->next = data->next;
    }
    else {
      parent->set.stream_dependents = data->next;
    }
    free(data);
  }

  child->set.stream_depends_on = 0;
  child->set.stream_depends_e = FALSE;
}