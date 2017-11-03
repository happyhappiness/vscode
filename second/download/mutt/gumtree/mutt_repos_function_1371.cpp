void mutt_set_parameter (const char *attribute, const char *value, PARAMETER **p)
{
  PARAMETER *q;

  if (!value)
  {
    mutt_delete_parameter (attribute, p);
    return;
  }
  
  for(q = *p; q; q = q->next)
  {
    if (ascii_strcasecmp (attribute, q->attribute) == 0)
    {
      mutt_str_replace (&q->value, value);
      return;
    }
  }
  
  q = mutt_new_parameter();
  q->attribute = safe_strdup(attribute);
  q->value = safe_strdup(value);
  q->next = *p;
  *p = q;
}