f(n->eid == eid) {
      Curl_llist_remove(timeoutlist, e, NULL);
      return;
    }