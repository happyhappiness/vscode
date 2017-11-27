static int mr_config_add_regex(mr_regex_t **re_head, /* {{{ */
                               oconfig_item_t *ci) {
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    log_warn("`%s' needs exactly one string argument.", ci->key);
    return -1;
  }

  return mr_add_regex(re_head, ci->values[0].value.string, ci->key);
}