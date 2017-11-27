static int vmem_config (const char *key, const char *value)
{
  if (strcasecmp ("Verbose", key) == 0)
  {
    if (IS_TRUE (value))
      verbose_output = 1;
    else
      verbose_output = 0;
  }
  else
  {
    return (-1);
  }

  return (0);
}