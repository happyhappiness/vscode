static void smart_read_disk(SkDisk *d, char const *name) {
  SkBool available = FALSE;
  if (sk_disk_identify_is_available(d, &available) < 0 || !available) {
    DEBUG("smart plugin: disk %s cannot be identified.", name);
    return;
  }
  if (sk_disk_smart_is_available(d, &available) < 0 || !available) {
    DEBUG("smart plugin: disk %s has no SMART support.", name);
    return;
  }
  if (!ignore_sleep_mode) {
    SkBool awake = FALSE;
    if (sk_disk_check_sleep_mode(d, &awake) < 0 || !awake) {
      DEBUG("smart plugin: disk %s is sleeping.", name);
      return;
    }
  }
  if (sk_disk_smart_read_data(d) < 0) {
    ERROR("smart plugin: unable to get SMART data for disk %s.", name);
    return;
  }

  if (sk_disk_smart_parse(d, &(SkSmartParsedData const *){NULL}) < 0