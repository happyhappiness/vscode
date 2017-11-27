static void cna_config_volume_usage_default(cfg_volume_usage_t *cvu, /* {{{ */
                                            const oconfig_item_t *ci) {
  ignorelist_t *il;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_BOOLEAN)) {
    WARNING(
        "netapp plugin: The %s option requires exactly one string argument.",
        ci->key);
    return;
  }

  if (strcasecmp("IgnoreSelectedCapacity", ci->key) == 0)
    il = cvu->il_capacity;
  else if (strcasecmp("IgnoreSelectedSnapshot", ci->key) == 0)
    il = cvu->il_snapshot;
  else
    return;

  if (ci->values[0].value.boolean)
    ignorelist_set_invert(il, /* invert = */ 0);
  else
    ignorelist_set_invert(il, /* invert = */ 1);
}