static int tr_destroy (void **user_data) /* {{{ */
{
  tr_data_t *data;

  if (user_data == NULL)
    return (-EINVAL);

  data = *user_data;
  if (data == NULL)
    return (0);

  tr_action_destroy (data->host);
  tr_action_destroy (data->plugin);
  tr_action_destroy (data->plugin_instance);
  /* tr_action_destroy (data->type); */
  tr_action_destroy (data->type_instance);
  sfree (data);

  return (0);
}