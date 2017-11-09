static void add_to_list (LIST **list, const char *str)
{
  LIST *t, *last = NULL;

  /* don't add a NULL or empty string to the list */
  if (!str || *str == '\0')
    return;

  /* check to make sure the item is not already on this list */
  for (last = *list; last; last = last->next)
  {
    if (ascii_strcasecmp (str, last->data) == 0)
    {
      /* already on the list, so just ignore it */
      last = NULL;
      break;
    }
    if (!last->next)
      break;
  }

  if (!*list || last)
  {
    t = (LIST *) safe_calloc (1, sizeof (LIST));
    t->data = safe_strdup (str);
    if (last)
    {
      last->next = t;
      last = last->next;
    }
    else
      *list = last = t;
  }
}