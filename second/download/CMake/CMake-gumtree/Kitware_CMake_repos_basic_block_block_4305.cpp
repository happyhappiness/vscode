{
    struct Curl_http2_dep **tail;
    struct Curl_http2_dep *dep = calloc(1, sizeof(struct Curl_http2_dep));
    dep->data = child;

    if(parent->set.stream_dependents && exclusive) {
      struct Curl_http2_dep *node = parent->set.stream_dependents;
      while(node) {
        node->data->set.stream_depends_on = child;
        node = node->next;
      }

      tail = &child->set.stream_dependents;
      while(*tail)
        tail = &(*tail)->next;

      DEBUGASSERT(!*tail);
      *tail = parent->set.stream_dependents;
      parent->set.stream_dependents = 0;
    }

    tail = &parent->set.stream_dependents;
    while(*tail) {
      (*tail)->data->set.stream_depends_e = FALSE;
      tail = &(*tail)->next;
    }

    DEBUGASSERT(!*tail);
    *tail = dep;
  }