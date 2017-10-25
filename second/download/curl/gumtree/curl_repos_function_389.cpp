static char *checkheaders(struct SessionHandle *data, const char *thisheader)
{
  struct curl_slist *head;
  size_t thislen = strlen(thisheader);

  for(head = data->set.headers; head; head=head->next) {
    if(strnequal(head->data, thisheader, thislen))
      return head->data;
  }
  return NULL;
}