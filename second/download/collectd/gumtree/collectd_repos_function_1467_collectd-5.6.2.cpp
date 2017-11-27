static void smart_handle_disk(const char *dev, const char *serial) {
  SkDisk *d = NULL;
  SkBool awake = FALSE;
  SkBool available = FALSE;
  const char *shortname;
  const SkSmartParsedData *spd;
  uint64_t poweron, powercycles, badsectors, temperature;

  if (use_serial && serial) {
    shortname = serial;
  } else {
    shortname = strrchr(dev, '/');
    if (!shortname)
      return;
    shortname++;
  }
  if (ignorelist_match(ignorelist, shortname) != 0) {
    DEBUG("smart plugin: ignoring %s.", dev);
    return;
  }

  DEBUG("smart plugin: checking SMART status of %s.", dev);

  if (sk_disk_open(dev, &d) < 0) {
    ERROR("smart plugin: unable to open %s.", dev);
    return;
  }
  if (sk_disk_identify_is_available(d, &available) < 0 || !available) {
    DEBUG("smart plugin: disk %s cannot be identified.", dev);
    goto end;
  }
  if (sk_disk_smart_is_available(d, &available) < 0 || !available) {
    DEBUG("smart plugin: disk %s has no SMART support.", dev);
    goto end;
  }
  if (!ignore_sleep_mode) {
    if (sk_disk_check_sleep_mode(d, &awake) < 0 || !awake) {
      DEBUG("smart plugin: disk %s is sleeping.", dev);
      goto end;
    }
  }
  if (sk_disk_smart_read_data(d) < 0) {
    ERROR("smart plugin: unable to get SMART data for disk %s.", dev);
    goto end;
  }
  if (sk_disk_smart_parse(d, &spd) < 0) {
    ERROR("smart plugin: unable to parse SMART data for disk %s.", dev);
    goto end;
  }

  /* Get some specific values */
  if (sk_disk_smart_get_power_on(d, &poweron) < 0) {
    WARNING("smart plugin: unable to get milliseconds since power on for %s.",
            dev);
  } else
    smart_submit(shortname, "smart_poweron", "", poweron / 1000.);

  if (sk_disk_smart_get_power_cycle(d, &powercycles) < 0) {
    WARNING("smart plugin: unable to get number of power cycles for %s.", dev);
  } else
    smart_submit(shortname, "smart_powercycles", "", powercycles);

  if (sk_disk_smart_get_bad(d, &badsectors) < 0) {
    WARNING("smart plugin: unable to get number of bad sectors for %s.", dev);
  } else
    smart_submit(shortname, "smart_badsectors", "", badsectors);

  if (sk_disk_smart_get_temperature(d, &temperature) < 0) {
    WARNING("smart plugin: unable to get temperature for %s.", dev);
  } else
    smart_submit(shortname, "smart_temperature", "",
                 temperature / 1000. - 273.15);

  /* Grab all attributes */
  if (sk_disk_smart_parse_attributes(d, smart_handle_disk_attribute,
                                     (char *)shortname) < 0) {
    ERROR("smart plugin: unable to handle SMART attributes for %s.", dev);
  }

end:
  sk_disk_free(d);
}