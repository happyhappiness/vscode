static int fc_bit_jump_create(const oconfig_item_t *ci, /* {{{ */
                              void **user_data) {
  oconfig_item_t *ci_chain;

  if (ci->children_num != 1) {
    ERROR("Filter subsystem: The built-in target `jump' needs exactly "
          "one `Chain' argument!");
    return -1;
  }

  ci_chain = ci->children;
  if (strcasecmp("Chain", ci_chain->key) != 0) {
    ERROR("Filter subsystem: The built-in target `jump' does not "
          "support the configuration option `%s'.",
          ci_chain->key);
    return -1;
  }

  if ((ci_chain->values_num != 1) ||
      (ci_chain->values[0].type != OCONFIG_TYPE_STRING)) {
    ERROR("Filter subsystem: Built-in target `jump': The `Chain' option "
          "needs exactly one string argument.");
    return -1;
  }

  *user_data = fc_strdup(ci_chain->values[0].value.string);
  if (*user_data == NULL) {
    ERROR("fc_bit_jump_create: fc_strdup failed.");
    return -1;
  }

  return 0;
}