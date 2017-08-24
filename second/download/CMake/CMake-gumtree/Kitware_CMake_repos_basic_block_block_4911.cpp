{
    struct curl_llist_element *n = e->next;
    time_t diff;
    node = (struct time_node *)e->ptr;
    diff = curlx_tvdiff(node->time, now);
    if(diff <= 0)
      /* remove outdated entry */
      Curl_llist_remove(list, e, NULL);
    else
      /* the list is sorted so get out on the first mismatch */
      break;
    e = n;
  }