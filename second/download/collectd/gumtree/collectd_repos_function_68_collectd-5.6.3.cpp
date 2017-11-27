SList *
slist_concat (SList *head, SList *tail)
{
  SList *last;

  if (!head)
    {
      return tail;
    }

  last = head;
  while (last->next)
    last = last->next;

  last->next = tail;

  return head;
}