static int lv_init_instance(size_t i, plugin_read_cb callback) {
  struct lv_user_data *lv_ud = &(lv_read_user_data[i]);
  struct lv_read_instance *inst = &(lv_ud->inst);

  memset(lv_ud, 0, sizeof(*lv_ud));

  snprintf(inst->tag, sizeof(inst->tag), "%s-%zu", PLUGIN_NAME, i);
  inst->id = i;

  user_data_t *ud = &(lv_ud->ud);
  ud->data = inst;
  ud->free_func = NULL;

  INFO(PLUGIN_NAME " plugin: reader %s initialized", inst->tag);
  return plugin_register_complex_read(NULL, inst->tag, callback, 0, ud);
}