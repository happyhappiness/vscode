void FreeMultiInfo(struct multi_files **multi_first,
                   struct multi_files **multi_last)
{
  struct multi_files *next;
  struct multi_files *item = *multi_first;

  while(item) {
    next = item->next;
    Curl_safefree(item);
    item = next;
  }
  *multi_first = NULL;
  if(multi_last)
    *multi_last = NULL;
}