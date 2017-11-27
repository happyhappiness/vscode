void smart_handle_disk(const char *dev, const char *serial) {
  SkDisk *d = NULL;
  const char *name;

  if (use_serial && serial) {
    name = serial;
  } else {
    name = strrchr(dev, '/');
    if (!name)
      return;
    name++;
  }
  if (ignorelist_match(ignorelist, name) != 0) {
    DEBUG("smart plugin: ignoring %s.", dev);
    return;
  }

  DEBUG("smart plugin: checking SMART status of %s.", dev);
  if (sk_disk_open(dev, &d) < 0) {
    ERROR("smart plugin: unable to open %s.", dev);
    return;
  }

  smart_read_disk(d, name);
  sk_disk_free(d);
}