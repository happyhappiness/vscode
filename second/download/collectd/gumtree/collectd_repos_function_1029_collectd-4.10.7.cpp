static int config_set (char **var, const char *value)
{
  if (*var != NULL)
  {
    free (*var);
    *var = NULL;
  }

  if ((*var = strdup (value)) == NULL)
    return (1);
  else
    return (0);
}