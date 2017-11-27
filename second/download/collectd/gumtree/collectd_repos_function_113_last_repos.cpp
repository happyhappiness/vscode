static void free_interface_devices(struct lv_read_state *state) {
  if (state->interface_devices) {
    for (int i = 0; i < state->nr_interface_devices; ++i) {
      sfree(state->interface_devices[i].path);
      sfree(state->interface_devices[i].address);
      sfree(state->interface_devices[i].number);
    }
    sfree(state->interface_devices);
  }
  state->interface_devices = NULL;
  state->nr_interface_devices = 0;
}