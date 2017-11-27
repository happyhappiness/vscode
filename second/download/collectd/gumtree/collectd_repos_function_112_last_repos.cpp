static int add_block_device(struct lv_read_state *state, virDomainPtr dom,
                            const char *path) {
  struct block_device *new_ptr;
  int new_size =
      sizeof(state->block_devices[0]) * (state->nr_block_devices + 1);
  char *path_copy;

  path_copy = strdup(path);
  if (!path_copy)
    return -1;

  if (state->block_devices)
    new_ptr = realloc(state->block_devices, new_size);
  else
    new_ptr = malloc(new_size);

  if (new_ptr == NULL) {
    sfree(path_copy);
    return -1;
  }
  state->block_devices = new_ptr;
  state->block_devices[state->nr_block_devices].dom = dom;
  state->block_devices[state->nr_block_devices].path = path_copy;
  return state->nr_block_devices++;
}