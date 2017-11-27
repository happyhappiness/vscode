static int tn_destroy(void **user_data) /* {{{ */
{
  tn_data_t *data;

  if (user_data == NULL)
    return (-EINVAL);

  data = *user_data;
  if (data == NULL)
    return (0);

  sfree(data->message);
  sfree(data);

  return (0);
}