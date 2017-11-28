SList *
slist_delete (SList *head, void (*delete_fct) (void *item))
{
  assert (delete_fct);

  while (head)
    {
      SList *next = head->next;
      (*delete_fct) (head);
      head = next;
    }

  return 0;
}