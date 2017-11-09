static char* mutt_find_cfg (const char *home, const char *xdg_cfg_home)
{
  const char* names[] =
  {
    "muttrc-" MUTT_VERSION,
    "muttrc",
    NULL,
  };

  const char* locations[][2] =
  {
    { home, ".", },
    { home, ".mutt/" },
    { xdg_cfg_home, "mutt/", },
    { NULL, NULL },
  };

  int i;

  for (i = 0; locations[i][0] || locations[i][1]; i++)
  {
    int j;

    if (!locations[i][0])
      continue;

    for (j = 0; names[j]; j++)
    {
      char buffer[STRING];

      snprintf (buffer, sizeof (buffer),
                "%s/%s%s", locations[i][0], locations[i][1], names[j]);
      if (access (buffer, F_OK) == 0)
        return safe_strdup(buffer);
    }
  }

  return NULL;
}