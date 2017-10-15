  }

  FREE(&s);
  return rc;
}

static int parse_setenv(BUFFER *tmp, BUFFER *s, unsigned long data, BUFFER *err)
{
  int query, unset, len;
  char work[LONG_STRING];
  char **save, **envp = envlist;
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
      set_option (OPTFORCEREDRAWINDEX);
      set_option (OPTFORCEREDRAWPAGER);
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

  /* Look for current slot to overwrite */
  count = 0;
  while (envp && *envp)
  {
    if (!mutt_strncmp (tmp->data, *envp, len) && (*envp)[len] == '=')
    {
      FREE (envp);     /* __FREE_CHECKED__ */
      break;
    }
    envp++;
    count++;
  }

  /* Format var=value string */
  strfcpy (work, tmp->data, sizeof(work));
  len = strlen (work);
  work[len++] = '=';
  mutt_extract_token (tmp, s, 0);
  strfcpy (&work[len], tmp->data, sizeof(work)-len);

  /* If slot found, overwrite */
  if (*envp)
    *envp = safe_strdup (work);

  /* If not found, add new slot */
  else
  {
    *envp = safe_strdup (work);
    count++;
    safe_realloc (&envlist, sizeof(char *) * (count + 1));
    envlist[count] = NULL;
  }

  return 0;
}

static int parse_set (BUFFER *tmp, BUFFER *s, unsigned long data, BUFFER *err)
{
  int query, unset, inv, reset, r = 0;
  int idx = -1;
  const char *p;
  char scratch[_POSIX_PATH_MAX];
