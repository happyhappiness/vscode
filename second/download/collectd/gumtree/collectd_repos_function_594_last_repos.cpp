static _Bool agg_is_regex(char const *str) /* {{{ */
{
  size_t len;

  if (str == NULL)
    return 0;

  len = strlen(str);
  if (len < 3)
    return 0;

  if ((str[0] == '/') && (str[len - 1] == '/'))
    return 1;
  else
    return 0;
}