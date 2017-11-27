static int meta_data_to_json (char *buffer, size_t buffer_size, /* {{{ */
    meta_data_t *meta)
{
  char **keys = NULL;
  size_t keys_num;
  int status;

  if ((buffer == NULL) || (buffer_size == 0) || (meta == NULL))
    return (EINVAL);

  status = meta_data_toc (meta, &keys);
  if (status <= 0)
    return (status);
  keys_num = (size_t) status;

  status = meta_data_keys_to_json (buffer, buffer_size, meta, keys, keys_num);

  for (size_t i = 0; i < keys_num; ++i)
    sfree (keys[i]);
  sfree (keys);

  return status;
}