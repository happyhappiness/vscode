static int config_set_char(char *dest, oconfig_item_t *ci) {
  char buffer[4] = {0};
  int status;

  status = cf_util_get_string_buffer(ci, buffer, sizeof(buffer));
  if (status != 0)
    return status;

  if (buffer[0] == 0) {
    ERROR("write_graphite plugin: Cannot use an empty string for the "
          "\"EscapeCharacter\" option.");
    return -1;
  }

  if (buffer[1] != 0) {
    WARNING("write_graphite plugin: Only the first character of the "
            "\"EscapeCharacter\" option ('%c') will be used.",
            (int)buffer[0]);
  }

  *dest = buffer[0];

  return 0;
}