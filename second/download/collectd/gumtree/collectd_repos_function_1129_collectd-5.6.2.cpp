static void cna_config_volume_perf_option(cfg_volume_perf_t *cvp, /* {{{ */
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

  if (strcasecmp("GetIO", ci->key) == 0)
    il = cvp->il_octets;
  else if (strcasecmp("GetOps", ci->key) == 0)
    il = cvp->il_operations;
  else if (strcasecmp("GetLatency", ci->key) == 0)
    il = cvp->il_latency;
  else
    return;

  ignorelist_add(il, name);
}