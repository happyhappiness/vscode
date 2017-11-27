static int fc_bit_write_destroy (void **user_data) /* {{{ */
{
  fc_writer_t *plugin_list;
  size_t i;

  if ((user_data == NULL) || (*user_data == NULL))
    return (0);

  plugin_list = *user_data;

  for (i = 0; plugin_list[i].plugin != NULL; i++)
    free (plugin_list[i].plugin);
  free (plugin_list);

  return (0);
}