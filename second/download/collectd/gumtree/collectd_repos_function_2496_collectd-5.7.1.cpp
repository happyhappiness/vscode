int uc_iterator_get_values(uc_iter_t *iter, value_t **ret_values,
                           size_t *ret_num) {
  if ((iter == NULL) || (iter->entry == NULL) || (ret_values == NULL) ||
      (ret_num == NULL))
    return (-1);

  *ret_values =
      calloc(iter->entry->values_num, sizeof(*iter->entry->values_raw));
  if (*ret_values == NULL)
    return (-1);
  for (size_t i = 0; i < iter->entry->values_num; ++i)
    *ret_values[i] = iter->entry->values_raw[i];

  *ret_num = iter->entry->values_num;

  return (0);
}