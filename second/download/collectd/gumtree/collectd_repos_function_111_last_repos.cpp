static void free_block_devices(struct lv_read_state *state) {
  if (state->block_devices) {
    for (int i = 0; i < state->nr_block_devices; ++i)
      sfree(state->block_devices[i].path);
    sfree(state->block_devices);
  }
  state->block_devices = NULL;
  state->nr_block_devices = 0;
}