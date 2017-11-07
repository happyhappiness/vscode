static void insert_message (THREAD **new, THREAD *newparent, THREAD *cur)
{
  if (*new)
    (*new)->prev = cur;

  cur->parent = newparent;
  cur->next = *new;
  cur->prev = NULL;
  *new = cur;
}