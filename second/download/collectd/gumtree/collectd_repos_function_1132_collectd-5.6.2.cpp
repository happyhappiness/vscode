static void cna_config_volume_usage_option(cfg_volume_usage_t *cvu, /* {{{ */
                                           const oconfig_item_t *ci) {
  char *name;
  ignorelist_t *il;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING(
        "netapp plugin: The %s option requires exactly one string argument.",
        ci->key);
    return;
  }

  name = ci->values[0].value.string;

  if (strcasecmp("GetCapacity", ci->key) == 0)
    il = cvu->il_capacity;
  else if (strcasecmp("GetSnapshot", ci->key) == 0)
    il = cvu->il_snapshot;
  else
    return;

  ignorelist_add(il, name);
}