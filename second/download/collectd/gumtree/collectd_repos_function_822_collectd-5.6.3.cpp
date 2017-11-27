static int bind_xml_list_callback(const char *name, /* {{{ */
                                  value_t value, time_t current_time,
                                  void *user_data) {
  list_info_ptr_t *list_info = (list_info_ptr_t *)user_data;

  if (list_info == NULL)
    return (-1);

  submit(current_time, list_info->plugin_instance, list_info->type,
         /* type instance = */ name, value);

  return (0);
}