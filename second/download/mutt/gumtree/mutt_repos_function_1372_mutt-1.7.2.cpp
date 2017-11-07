void mutt_delete_parameter (const char *attribute, PARAMETER **p)
{
  PARAMETER *q;
  
  for (q = *p; q; p = &q->next, q = q->next)
  {
    if (ascii_strcasecmp (attribute, q->attribute) == 0)
    {
      *p = q->next;
      q->next = NULL;
      mutt_free_parameter (&q);
      return;
    }
  }
}