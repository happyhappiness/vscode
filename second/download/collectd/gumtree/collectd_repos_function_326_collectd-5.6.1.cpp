static int ir_config (const char *key, const char *value)
{
  char *new_val;
  char *fields[8];
  int fields_num;
  int status = 1;

  new_val = strdup (value);
  if (new_val == NULL)
    return (-1);

  fields_num = strsplit (new_val, fields, STATIC_ARRAY_SIZE (fields));
  if ((fields_num < 1) || (fields_num > 8))
  {
    sfree (new_val);
    return (-1);
  }

  if ((strcasecmp (key, "Interface") == 0)
      || (strcasecmp (key, "VerboseInterface") == 0))
  {
    if (fields_num != 1)
    {
      ERROR ("netlink plugin: Invalid number of fields for option "
          "`%s'. Got %i, expected 1.", key, fields_num);
      status = -1;
    }
    else
    {
      add_ignorelist (fields[0], "interface", NULL);
      if (strcasecmp (key, "VerboseInterface") == 0)
        add_ignorelist (fields[0], "if_detail", NULL);
      status = 0;
    }
  }
  else if ((strcasecmp (key, "QDisc") == 0)
      || (strcasecmp (key, "Class") == 0)
      || (strcasecmp (key, "Filter") == 0))
  {
    if ((fields_num < 1) || (fields_num > 2))
    {
      ERROR ("netlink plugin: Invalid number of fields for option "
          "`%s'. Got %i, expected 1 or 2.", key, fields_num);
      return (-1);
    }
    else
    {
      add_ignorelist (fields[0], key,
          (fields_num == 2) ? fields[1] : NULL);
      status = 0;
    }
  }
  else if (strcasecmp (key, "IgnoreSelected") == 0)
  {
    if (fields_num != 1)
    {
      ERROR ("netlink plugin: Invalid number of fields for option "
          "`IgnoreSelected'. Got %i, expected 1.", fields_num);
      status = -1;
    }
    else
    {
      if (IS_TRUE (fields[0]))
        ir_ignorelist_invert = 0;
      else
        ir_ignorelist_invert = 1;
      status = 0;
    }
  }

  sfree (new_val);

  return (status);
}