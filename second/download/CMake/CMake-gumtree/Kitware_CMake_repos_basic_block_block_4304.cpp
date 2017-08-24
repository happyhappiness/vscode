{
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