static int parse_setenv(BUFFER *tmp, BUFFER *s, unsigned long data, BUFFER *err)
{
  int query, unset, len;
  char *name, **save, **envp = envlist;
  int count = 0;

  query = 0;
  unset = data & MUTT_SET_UNSET;

  if (!MoreArgs (s))
  {
    strfcpy (err->data, _("too few arguments"), err->dsize);
    return -1;
  }

  if (*s->dptr == '?')
  {
    query = 1;
    s->dptr++;
  }

  /* get variable name */
  mutt_extract_token (tmp, s, MUTT_TOKEN_EQUAL);
  len = strlen (tmp->data);

  if (query)
  {
    int found = 0;
    while (envp && *envp)
    {
      if (!mutt_strncmp (tmp->data, *envp, len))
      {
        if (!found)
        {
          mutt_endwin (NULL);
          found = 1;
        }
        puts (*envp);
      }
      envp++;
    }

    if (found)
    {
      mutt_any_key_to_continue (NULL);
      return 0;
    }

    snprintf (err->data, err->dsize, _("%s is unset"), tmp->data);
    return -1;
  }

  if (unset)
  {
    count = 0;
    while (envp && *envp)
    {
      if (!mutt_strncmp (tmp->data, *envp, len) && (*envp)[len] == '=')
      {
        /* shuffle down */
        save = envp++;
        while (*envp)
        {
          *save++ = *envp++;
          count++;
        }
        *save = NULL;
        safe_realloc (&envlist, sizeof(char *) * (count+1));
        return 0;
      }
      envp++;
      count++;
    }
    return -1;
  }

  /* set variable */

  if (*s->dptr == '=')
  {
    s->dptr++;
    SKIPWS (s->dptr);
  }

  if (!MoreArgs (s))
  {
    strfcpy (err->data, _("too few arguments"), err->dsize);
    return -1;
  }

  name = safe_strdup (tmp->data);
  mutt_extract_token (tmp, s, 0);
  mutt_envlist_set (name, tmp->data, 1);
  FREE (&name);

  return 0;
}