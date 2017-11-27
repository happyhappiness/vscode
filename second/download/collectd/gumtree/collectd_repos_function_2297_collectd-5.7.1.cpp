static int ts_destroy(void **user_data) /* {{{ */
{
  ts_data_t *data;

  if (user_data == NULL)
    return (-EINVAL);

  data = (ts_data_t *)*user_data;

  if ((data != NULL) && (data->data_sources != NULL)) {
    for (size_t i = 0; i < data->data_sources_num; i++)
      sfree(data->data_sources[i]);
    sfree(data->data_sources);
  }

  sfree(data);
  *user_data = NULL;

  return (0);
}