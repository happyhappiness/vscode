char *mutt_extract_message_id (const char *s, const char **saveptr)
{
  const char *o, *onull, *p;
  char *ret = NULL;

  if (s)
    p = s;
  else if (saveptr)
    p = *saveptr;
  else
    return NULL;

  for (s = NULL, o = NULL, onull = NULL;
       (p = strpbrk (p, "<> \t;")) != NULL; ++p)
  {
    if (*p == '<')
    {
      s = p; 
      o = onull = NULL;
      continue;
    }

    if (!s)
      continue;

    if (*p == '>')
    {
      size_t olen = onull - o, slen = p - s + 1;
      ret = safe_malloc (olen + slen + 1);
      if (o)
	memcpy (ret, o, olen);
      memcpy (ret + olen, s, slen);
      ret[olen + slen] = '\0';
      if (saveptr)
	*saveptr = p + 1; /* next call starts after '>' */
      return ret;
    }

    /* some idiotic clients break their message-ids between lines */
    if (s == p) 
      /* step past another whitespace */
      s = p + 1;
    else if (o)
      /* more than two lines, give up */
      s = o = onull = NULL;
    else
    {
      /* remember the first line, start looking for the second */
      o = s;
      onull = p;
      s = p + 1;
    }
  }

  return NULL;
}