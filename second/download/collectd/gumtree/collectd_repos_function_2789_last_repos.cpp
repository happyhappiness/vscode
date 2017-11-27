int cf_util_get_string_buffer(const oconfig_item_t *ci, char *buffer, /* {{{ */
                              size_t buffer_size) {
  if ((ci == NULL) || (buffer == NULL) || (buffer_size < 1))
    return EINVAL;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    ERROR("cf_util_get_string_buffer: The %s option requires "
          "exactly one string argument.",
          ci->key);
    return -1;
  }

  strncpy(buffer, ci->values[0].value.string, buffer_size);
  buffer[buffer_size - 1] = 0;

  return 0;
}