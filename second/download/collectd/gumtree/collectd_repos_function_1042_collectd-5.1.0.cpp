static void strset (char **str, const char *new) /* {{{ */
{
  char *tmp;

  if (!str || !new)
    return;

  tmp = strdup (new);
  if (tmp == NULL)
    return;

  sfree (*str);
  *str = tmp;
}