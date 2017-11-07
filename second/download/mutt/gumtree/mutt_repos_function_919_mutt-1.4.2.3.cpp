LIST *mutt_add_list (LIST *head, const char *data)
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

  tmp->data = safe_strdup (data);
  tmp->next = NULL;
  return head;
}