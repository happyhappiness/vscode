static void lv_fini_instance(size_t i) {
  struct lv_read_instance *inst = &(lv_read_user_data[i].inst);
  struct lv_read_state *state = &(inst->read_state);

  lv_clean_read_state(state);
  INFO(PLUGIN_NAME " plugin: reader %s finalized", inst->tag);
}