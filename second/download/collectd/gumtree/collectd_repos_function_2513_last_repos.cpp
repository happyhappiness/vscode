static int parse_identifier(uint16_t type, void *payload, size_t payload_size,
                            lcc_value_list_t *state) {
  char buf[LCC_NAME_LEN];

  if (parse_string(payload, payload_size, buf, sizeof(buf)) != 0)
    return EINVAL;

  switch (type) {
  case TYPE_HOST:
    memmove(state->identifier.host, buf, LCC_NAME_LEN);
    break;
  case TYPE_PLUGIN:
    memmove(state->identifier.plugin, buf, LCC_NAME_LEN);
    break;
  case TYPE_PLUGIN_INSTANCE:
    memmove(state->identifier.plugin_instance, buf, LCC_NAME_LEN);
    break;
  case TYPE_TYPE:
    memmove(state->identifier.type, buf, LCC_NAME_LEN);
    break;
  case TYPE_TYPE_INSTANCE:
    memmove(state->identifier.type_instance, buf, LCC_NAME_LEN);
    break;
  default:
    return EINVAL;
  }

  return 0;
}