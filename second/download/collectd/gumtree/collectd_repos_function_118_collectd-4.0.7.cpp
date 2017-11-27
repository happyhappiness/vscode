static int exec_config (const char *key, const char *value)
{
  if (strcasecmp ("Exec", key) == 0)
  {
    program_list_t *pl;
    pl = (program_list_t *) malloc (sizeof (program_list_t));
    if (pl == NULL)
      return (1);
    memset (pl, '\0', sizeof (program_list_t));

    pl->user = strdup (value);
    if (pl->user == NULL)
    {
      sfree (pl);
      return (1);
    }

    pl->exec = strchr (pl->user, ' ');
    if (pl->exec == NULL)
    {
      sfree (pl->user);
      sfree (pl);
      return (1);
    }
    while (*pl->exec == ' ')
    {
      *pl->exec = '\0';
      pl->exec++;
    }

    if (*pl->exec == '\0')
    {
      sfree (pl->user);
      sfree (pl);
      return (1);
    }

    pl->next = pl_head;
    pl_head = pl;
  }
  else
  {
    return (-1);
  }

  return (0);
}