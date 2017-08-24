{
    next = item->next;
    Curl_safefree(item->data);
    free(item);
    item = next;
  }