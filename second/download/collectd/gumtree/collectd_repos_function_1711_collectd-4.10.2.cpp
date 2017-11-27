static int ts_destroy (void **user_data) /* {{{ */
{
  ts_data_t *data;

  if (user_data == NULL)
    return (-EINVAL);

  data = *user_data;
  if (data == NULL)
    return (0);

  free (data->host);
  free (data->plugin);
  free (data->plugin_instance);
  /* free (data->type); */
  free (data->type_instance);
  free (data);

  return (0);
}