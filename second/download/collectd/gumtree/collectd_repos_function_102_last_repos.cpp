static void lv_clean_read_state(struct lv_read_state *state) {
  free_block_devices(state);
  free_interface_devices(state);
  free_domains(state);
}