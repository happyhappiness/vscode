static char* msg_parse_flags (IMAP_HEADER* h, char* s)
{
  int recent = 0;

  /* sanity-check string */
  if (ascii_strncasecmp ("FLAGS", s, 5) != 0)
  {
    dprint (1, (debugfile, "msg_parse_flags: not a FLAGS response: %s\n",
      s));
    return NULL;
  }
  s += 5;
  SKIPWS(s);
  if (*s != '(')
  {
    dprint (1, (debugfile, "msg_parse_flags: bogus FLAGS response: %s\n",
      s));
    return NULL;
  }
  s++;

  /* start parsing */
  while (*s && *s != ')')
  {
    if (ascii_strncasecmp ("\\deleted", s, 8) == 0)
    {
      s += 8;
      h->deleted = 1;
    }
    else if (ascii_strncasecmp ("\\flagged", s, 8) == 0)
    {
      s += 8;
      h->flagged = 1;
    }
    else if (ascii_strncasecmp ("\\answered", s, 9) == 0)
    {
      s += 9;
      h->replied = 1;
    }
    else if (ascii_strncasecmp ("\\seen", s, 5) == 0)
    {
      s += 5;
      h->read = 1;
    }
    else if (ascii_strncasecmp ("\\recent", s, 5) == 0)
    {
      s += 7;
      recent = 1;
    }
    else
    {
      /* store custom flags as well */
      char ctmp;
      char* flag_word = s;

      if (!h->data->keywords)
        h->data->keywords = mutt_new_list ();

      while (*s && !ISSPACE (*s) && *s != ')')
        s++;
      ctmp = *s;
      *s = '\0';
      mutt_add_list (h->data->keywords, flag_word);
      *s = ctmp;
    }
    SKIPWS(s);
  }

  /* wrap up, or note bad flags response */
  if (*s == ')')
  {
    /* if a message is neither seen nor recent, it is OLD. */
    if (option (OPTMARKOLD) && !recent && !(h->read))
      h->old = 1;
    s++;
  }
  else
  {
    dprint (1, (debugfile,
      "msg_parse_flags: Unterminated FLAGS response: %s\n", s));
    return NULL;
  }

  return s;
}