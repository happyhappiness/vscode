static int udb_config_add_string (char ***ret_array, /* {{{ */
    size_t *ret_array_len, oconfig_item_t *ci)
{
  char **array;
  size_t array_len;
  int i;

  if (ci->values_num < 1)
  {
    WARNING ("db query utils: The `%s' config option "
        "needs at least one argument.", ci->key);
    return (-1);
  }

  for (i = 0; i < ci->values_num; i++)
  {
    if (ci->values[i].type != OCONFIG_TYPE_STRING)
    {
      WARNING ("db query utils: Argument %i to the `%s' option "
          "is not a string.", i + 1, ci->key);
      return (-1);
    }
  }

  array_len = *ret_array_len;
  array = (char **) realloc (*ret_array,
      sizeof (char *) * (array_len + ci->values_num));
  if (array == NULL)
  {
    ERROR ("db query utils: realloc failed.");
    return (-1);
  }
  *ret_array = array;

  for (i = 0; i < ci->values_num; i++)
  {
    array[array_len] = strdup (ci->values[i].value.string);
    if (array[array_len] == NULL)
    {
      ERROR ("db query utils: strdup failed.");
      *ret_array_len = array_len;
      return (-1);
    }
    array_len++;
  }

  *ret_array_len = array_len;
  return (0);
}