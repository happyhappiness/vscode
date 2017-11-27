static int add_interface_device(struct lv_read_state *state, virDomainPtr dom,
                                const char *path, const char *address,
                                unsigned int number) {
  struct interface_device *new_ptr;
  int new_size =
      sizeof(state->interface_devices[0]) * (state->nr_interface_devices + 1);
  char *path_copy, *address_copy, number_string[15];

  if ((path == NULL) || (address == NULL))
    return EINVAL;

  path_copy = strdup(path);
  if (!path_copy)
    return -1;

  address_copy = strdup(address);
  if (!address_copy) {
    sfree(path_copy);
    return -1;
  }

  snprintf(number_string, sizeof(number_string), "interface-%u", number);

  if (state->interface_devices)
    new_ptr = realloc(state->interface_devices, new_size);
  else
    new_ptr = malloc(new_size);

  if (new_ptr == NULL) {
    sfree(path_copy);
    sfree(address_copy);
    return -1;
  }
  state->interface_devices = new_ptr;
  state->interface_devices[state->nr_interface_devices].dom = dom;
  state->interface_devices[state->nr_interface_devices].path = path_copy;
  state->interface_devices[state->nr_interface_devices].address = address_copy;
  state->interface_devices[state->nr_interface_devices].number =
      strdup(number_string);
  return state->nr_interface_devices++;
}