static int json_add_string (yajl_gen g, char const *str) /* {{{ */
{
  if (str == NULL)
    return (int) yajl_gen_null (g);

  return (int) yajl_gen_string (g, (unsigned char const *) str, (unsigned int) strlen (str));
}