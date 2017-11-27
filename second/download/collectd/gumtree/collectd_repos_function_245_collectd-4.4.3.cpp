static int nut_config (const char *key, const char *value)
{
  if (strcasecmp (key, "UPS") == 0)
    return (nut_add_ups (value));
  else
    return (-1);
}