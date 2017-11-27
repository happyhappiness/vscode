static int exec_config_exec (oconfig_item_t *ci) /* {{{ */
{
  program_list_t *pl;
  char buffer[128];
  int i;

  if (ci->children_num != 0)
  {
    WARNING ("exec plugin: The config option `%s' may not be a block.",
	ci->key);
    return (-1);
  }
  if (ci->values_num < 2)
  {
    WARNING ("exec plugin: The config option `%s' needs at least two "
	"arguments.", ci->key);
    return (-1);
  }
  if ((ci->values[0].type != OCONFIG_TYPE_STRING)
      || (ci->values[1].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("exec plugin: The first two arguments to the `%s' option must "
	"be string arguments.", ci->key);
    return (-1);
  }

  pl = (program_list_t *) malloc (sizeof (program_list_t));
  if (pl == NULL)
  {
    ERROR ("exec plugin: malloc failed.");
    return (-1);
  }
  memset (pl, '\0', sizeof (program_list_t));

  if (strcasecmp ("NotificationExec", ci->key) == 0)
    pl->flags |= PL_NOTIF_ACTION;
  else
    pl->flags |= PL_NORMAL;

  pl->user = strdup (ci->values[0].value.string);
  if (pl->user == NULL)
  {
    ERROR ("exec plugin: strdup failed.");
    sfree (pl);
    return (-1);
  }

  pl->group = strchr (pl->user, ':');
  if (pl->group != NULL)
  {
    *pl->group = '\0';
    pl->group++;
  }

  pl->exec = strdup (ci->values[1].value.string);
  if (pl->exec == NULL)
  {
    ERROR ("exec plugin: strdup failed.");
    sfree (pl->user);
    sfree (pl);
    return (-1);
  }

  pl->argv = (char **) malloc (ci->values_num * sizeof (char *));
  if (pl->argv == NULL)
  {
    ERROR ("exec plugin: malloc failed.");
    sfree (pl->exec);
    sfree (pl->user);
    sfree (pl);
    return (-1);
  }
  memset (pl->argv, '\0', ci->values_num * sizeof (char *));

  {
    char *tmp = strrchr (ci->values[1].value.string, '/');
    if (tmp == NULL)
      sstrncpy (buffer, ci->values[1].value.string, sizeof (buffer));
    else
      sstrncpy (buffer, tmp + 1, sizeof (buffer));
  }
  pl->argv[0] = strdup (buffer);
  if (pl->argv[0] == NULL)
  {
    ERROR ("exec plugin: malloc failed.");
    sfree (pl->argv);
    sfree (pl->exec);
    sfree (pl->user);
    sfree (pl);
    return (-1);
  }

  for (i = 1; i < (ci->values_num - 1); i++)
  {
    if (ci->values[i + 1].type == OCONFIG_TYPE_STRING)
    {
      pl->argv[i] = strdup (ci->values[i + 1].value.string);
    }
    else
    {
      if (ci->values[i + 1].type == OCONFIG_TYPE_NUMBER)
      {
	ssnprintf (buffer, sizeof (buffer), "%lf",
	    ci->values[i + 1].value.number);
      }
      else
      {
	if (ci->values[i + 1].value.boolean)
	  sstrncpy (buffer, "true", sizeof (buffer));
	else
	  sstrncpy (buffer, "false", sizeof (buffer));
      }

      pl->argv[i] = strdup (buffer);
    }

    if (pl->argv[i] == NULL)
    {
      ERROR ("exec plugin: strdup failed.");
      break;
    }
  } /* for (i) */

  if (i < (ci->values_num - 1))
  {
    while ((--i) >= 0)
    {
      sfree (pl->argv[i]);
    }
    sfree (pl->argv);
    sfree (pl->exec);
    sfree (pl->user);
    sfree (pl);
    return (-1);
  }

  for (i = 0; pl->argv[i] != NULL; i++)
  {
    DEBUG ("exec plugin: argv[%i] = %s", i, pl->argv[i]);
  }

  pl->next = pl_head;
  pl_head = pl;

  return (0);
}