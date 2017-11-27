static int redis_handle_info (char *node, char const *info_line, char const *type, char const *type_instance, char const *field_name, int ds_type) /* {{{ */
{
  char *str = strstr (info_line, field_name);
  static char buf[MAX_REDIS_VAL_SIZE];
  value_t val;
  if (str)
  {
    int i;

    str += strlen (field_name) + 1; /* also skip the ':' */
    for(i=0;(*str && (isdigit((unsigned char)*str) || *str == '.'));i++,str++)
      buf[i] = *str;
    buf[i] ='\0';

    if(parse_value (buf, &val, ds_type) == -1)
    {
      WARNING ("redis plugin: Unable to parse field `%s'.", field_name);
      return (-1);
    }

    redis_submit (node, type, type_instance, val);
    return (0);
  }
  return (-1);

}