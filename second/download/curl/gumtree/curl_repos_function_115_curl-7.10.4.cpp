static bool
checkhttpprefix(struct SessionHandle *data,
                const char *s)
{
  struct curl_slist *head = data->set.http200aliases;

  while (head) {
    if (checkprefix(head->data, s))
      return TRUE;
    head = head->next;
  }

  if(checkprefix("HTTP/", s))
    return TRUE;

  return FALSE;
}