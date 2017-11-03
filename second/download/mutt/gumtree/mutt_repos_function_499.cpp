static LIST *mutt_parse_references (char *s, int in_reply_to)
{
  LIST *t, *lst = NULL;
  char *m;
  const char *sp;

  m = mutt_extract_message_id (s, &sp);
  while (m)
  {
    t = safe_malloc (sizeof (LIST));
    t->data = m;
    t->next = lst;
    lst = t;

    m = mutt_extract_message_id (NULL, &sp);
  }

  return lst;
}