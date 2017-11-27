static int oconfig_to_cgroups(oconfig_item_t *item, rdt_core_group_t *groups,
                              size_t max_groups) {
  int index = 0;

  assert(groups != NULL);
  assert(max_groups > 0);
  assert(item != NULL);

  for (int j = 0; j < item->values_num; j++) {
    int ret;
    size_t n;
    uint64_t cores[RDT_MAX_CORES] = {0};
    char value[DATA_MAX_NAME_LEN];

    if ((item->values[j].value.string == NULL) ||
        (strlen(item->values[j].value.string) == 0))
      continue;

    sstrncpy(value, item->values[j].value.string, sizeof(value));

    n = strlisttonums(value, cores, STATIC_ARRAY_SIZE(cores));
    if (n == 0) {
      ERROR(RDT_PLUGIN ": Error parsing core group (%s)",
            item->values[j].value.string);
      return -EINVAL;
    }

    /* set core group info */
    ret = cgroup_set(&groups[index], item->values[j].value.string, cores, n);
    if (ret < 0)
      return ret;

    index++;

    if (index >= max_groups) {
      WARNING(RDT_PLUGIN ": Too many core groups configured");
      return index;
    }
  }

  return index;
}