LIST *mutt_add_list_n (LIST *head, const void *data, size_t len)
{
  LIST *tmp;
  
  for (tmp = head; tmp && tmp->next; tmp = tmp->next)
    ;
  if (tmp)
  {
    tmp->next = safe_malloc (sizeof (LIST));
    tmp = tmp->next;
  }
  else
    head = tmp = safe_malloc (sizeof (LIST));
  
  tmp->data = safe_malloc (len);
  if (len)
    memcpy (tmp->data, data, len);
  tmp->next = NULL;
  return head;
}