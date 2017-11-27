static int c_ipmi_read(user_data_t *user_data) {
  c_ipmi_instance_t *st = user_data->data;

  if (st->active == 0) {
    INFO("ipmi plugin: c_ipmi_read: I'm not active, returning false.");
    return -1;
  }

  if (st->connected == 0)
    return 0;

  sensor_list_read_all(st);

  if (st->init_in_progress > 0)
    st->init_in_progress--;
  else
    st->init_in_progress = 0;

  return 0;
}