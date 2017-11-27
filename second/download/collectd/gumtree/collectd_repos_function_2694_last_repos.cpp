int strarray_add(char ***ret_array, size_t *ret_array_len,
                 char const *str) /* {{{ */
{
  char **array;
  size_t array_len = *ret_array_len;

  if (str == NULL)
    return EINVAL;

  array = realloc(*ret_array, (array_len + 1) * sizeof(*array));
  if (array == NULL)
    return ENOMEM;
  *ret_array = array;

  array[array_len] = strdup(str);
  if (array[array_len] == NULL)
    return ENOMEM;

  array_len++;
  *ret_array_len = array_len;
  return 0;
}