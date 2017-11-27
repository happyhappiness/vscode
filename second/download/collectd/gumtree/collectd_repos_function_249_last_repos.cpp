static int qos_attr_cb(const struct nlattr *attr, void *data) {
  struct qos_stats *q_stats = (struct qos_stats *)data;

  /* skip unsupported attribute in user-space */
  if (mnl_attr_type_valid(attr, TCA_STATS_MAX) < 0)
    return MNL_CB_OK;

  if (mnl_attr_get_type(attr) == TCA_STATS_BASIC) {
    if (mnl_attr_validate2(attr, MNL_TYPE_UNSPEC, sizeof(*q_stats->bs)) < 0) {
      char errbuf[1024];
      ERROR("netlink plugin: qos_attr_cb: TCA_STATS_BASIC mnl_attr_validate2 "
            "failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      return MNL_CB_ERROR;
    }
    q_stats->bs = mnl_attr_get_payload(attr);
    return MNL_CB_OK;
  }

  if (mnl_attr_get_type(attr) == TCA_STATS_QUEUE) {
    if (mnl_attr_validate2(attr, MNL_TYPE_UNSPEC, sizeof(*q_stats->qs)) < 0) {
      ERROR("netlink plugin: qos_attr_cb: TCA_STATS_QUEUE mnl_attr_validate2 "
            "failed.");
      return MNL_CB_ERROR;
    }
    q_stats->qs = mnl_attr_get_payload(attr);
    return MNL_CB_OK;
  }

  return MNL_CB_OK;
}