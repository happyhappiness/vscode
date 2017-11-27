static int qos_attr_cb(const struct nlattr *attr, void *data) {
  struct gnet_stats_basic **bs = (struct gnet_stats_basic **)data;

  /* skip unsupported attribute in user-space */
  if (mnl_attr_type_valid(attr, TCA_STATS_MAX) < 0)
    return MNL_CB_OK;

  if (mnl_attr_get_type(attr) == TCA_STATS_BASIC) {
    if (mnl_attr_validate2(attr, MNL_TYPE_UNSPEC, sizeof(**bs)) < 0) {
      ERROR("netlink plugin: qos_attr_cb: TCA_STATS_BASIC mnl_attr_validate2 "
            "failed.");
      return MNL_CB_ERROR;
    }
    *bs = mnl_attr_get_payload(attr);
    return MNL_CB_STOP;
  }

  return MNL_CB_OK;
}