void mutt_envlist_set (const char *name, const char *value, int overwrite)
{
  char **envp = envlist;
  char work[LONG_STRING];
  int count, len;

  len = mutt_strlen (name);

  /* Look for current slot to overwrite */
  count = 0;
  while (envp && *envp)
  {
    if (!mutt_strncmp (name, *envp, len) && (*envp)[len] == '=')
    {
      if (!overwrite)
        return;
      break;
    }
    envp++;
    count++;
  }

  /* Format var=value string */
  snprintf (work, sizeof(work), "%s=%s", NONULL (name), NONULL (value));

  /* If slot found, overwrite */
  if (envp && *envp)
    mutt_str_replace (envp, work);

  /* If not found, add new slot */
  else
  {
    safe_realloc (&envlist, sizeof(char *) * (count + 2));
    envlist[count] = safe_strdup (work);
    envlist[count + 1] = NULL;
  }
}