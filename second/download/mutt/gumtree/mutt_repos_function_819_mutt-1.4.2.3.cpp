static void encode_headers (LIST *h)
{
  char *tmp;
  char *p;
  int i;
  
  for (; h; h = h->next)
  {
    if (!(p = strchr (h->data, ':')))
      continue;

    i = p - h->data;
    ++p; SKIPWS (p);
    tmp = safe_strdup (p);

    if (!tmp)
      continue;
    
    rfc2047_encode_string (&tmp);
    safe_realloc ((void **) &h->data, 
		  mutt_strlen (h->data) + 2 + mutt_strlen (tmp) + 1);

    sprintf (h->data + i, ": %s", NONULL (tmp));  /* __SPRINTF_CHECKED__ */
    
    safe_free ((void **) &tmp);
  }
}