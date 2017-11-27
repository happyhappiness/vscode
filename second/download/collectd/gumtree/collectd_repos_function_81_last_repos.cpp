static int lv_config(const char *key, const char *value) {
  if (virInitialize() != 0)
    return 1;

  if (il_domains == NULL)
    il_domains = ignorelist_create(1);
  if (il_block_devices == NULL)
    il_block_devices = ignorelist_create(1);
  if (il_interface_devices == NULL)
    il_interface_devices = ignorelist_create(1);

  if (strcasecmp(key, "Connection") == 0) {
    char *tmp = strdup(value);
    if (tmp == NULL) {
      ERROR(PLUGIN_NAME " plugin: Connection strdup failed.");
      return 1;
    }
    sfree(conn_string);
    conn_string = tmp;
    return 0;
  }

  if (strcasecmp(key, "RefreshInterval") == 0) {
    char *eptr = NULL;
    interval = strtol(value, &eptr, 10);
    if (eptr == NULL || *eptr != '\0')
      return 1;
    return 0;
  }

  if (strcasecmp(key, "Domain") == 0) {
    if (ignorelist_add(il_domains, value))
      return 1;
    return 0;
  }
  if (strcasecmp(key, "BlockDevice") == 0) {
    if (ignorelist_add(il_block_devices, value))
      return 1;
    return 0;
  }

  if (strcasecmp(key, "BlockDeviceFormat") == 0) {
    if (strcasecmp(value, "target") == 0)
      blockdevice_format = target;
    else if (strcasecmp(value, "source") == 0)
      blockdevice_format = source;
    else {
      ERROR(PLUGIN_NAME " plugin: unknown BlockDeviceFormat: %s", value);
      return -1;
    }
    return 0;
  }
  if (strcasecmp(key, "BlockDeviceFormatBasename") == 0) {
    blockdevice_format_basename = IS_TRUE(value);
    return 0;
  }
  if (strcasecmp(key, "InterfaceDevice") == 0) {
    if (ignorelist_add(il_interface_devices, value))
      return 1;
    return 0;
  }

  if (strcasecmp(key, "IgnoreSelected") == 0) {
    if (IS_TRUE(value)) {
      ignorelist_set_invert(il_domains, 0);
      ignorelist_set_invert(il_block_devices, 0);
      ignorelist_set_invert(il_interface_devices, 0);
    } else {
      ignorelist_set_invert(il_domains, 1);
      ignorelist_set_invert(il_block_devices, 1);
      ignorelist_set_invert(il_interface_devices, 1);
    }
    return 0;
  }

  if (strcasecmp(key, "HostnameFormat") == 0) {
    char *value_copy;
    char *fields[HF_MAX_FIELDS];
    int n;

    value_copy = strdup(value);
    if (value_copy == NULL) {
      ERROR(PLUGIN_NAME " plugin: strdup failed.");
      return -1;
    }

    n = strsplit(value_copy, fields, HF_MAX_FIELDS);
    if (n < 1) {
      sfree(value_copy);
      ERROR(PLUGIN_NAME " plugin: HostnameFormat: no fields");
      return -1;
    }

    for (int i = 0; i < n; ++i) {
      if (strcasecmp(fields[i], "hostname") == 0)
        hostname_format[i] = hf_hostname;
      else if (strcasecmp(fields[i], "name") == 0)
        hostname_format[i] = hf_name;
      else if (strcasecmp(fields[i], "uuid") == 0)
        hostname_format[i] = hf_uuid;
      else {
        ERROR(PLUGIN_NAME " plugin: unknown HostnameFormat field: %s",
              fields[i]);
        sfree(value_copy);
        return -1;
      }
    }
    sfree(value_copy);

    for (int i = n; i < HF_MAX_FIELDS; ++i)
      hostname_format[i] = hf_none;

    return 0;
  }

  if (strcasecmp(key, "PluginInstanceFormat") == 0) {
    char *value_copy;
    char *fields[PLGINST_MAX_FIELDS];
    int n;

    value_copy = strdup(value);
    if (value_copy == NULL) {
      ERROR(PLUGIN_NAME " plugin: strdup failed.");
      return -1;
    }

    n = strsplit(value_copy, fields, PLGINST_MAX_FIELDS);
    if (n < 1) {
      sfree(value_copy);
      ERROR(PLUGIN_NAME " plugin: PluginInstanceFormat: no fields");
      return -1;
    }

    for (int i = 0; i < n; ++i) {
      if (strcasecmp(fields[i], "none") == 0) {
        plugin_instance_format[i] = plginst_none;
        break;
      } else if (strcasecmp(fields[i], "name") == 0)
        plugin_instance_format[i] = plginst_name;
      else if (strcasecmp(fields[i], "uuid") == 0)
        plugin_instance_format[i] = plginst_uuid;
      else {
        ERROR(PLUGIN_NAME " plugin: unknown PluginInstanceFormat field: %s",
              fields[i]);
        sfree(value_copy);
        return -1;
      }
    }
    sfree(value_copy);

    for (int i = n; i < PLGINST_MAX_FIELDS; ++i)
      plugin_instance_format[i] = plginst_none;

    return 0;
  }

  if (strcasecmp(key, "InterfaceFormat") == 0) {
    if (strcasecmp(value, "name") == 0)
      interface_format = if_name;
    else if (strcasecmp(value, "address") == 0)
      interface_format = if_address;
    else if (strcasecmp(value, "number") == 0)
      interface_format = if_number;
    else {
      ERROR(PLUGIN_NAME " plugin: unknown InterfaceFormat: %s", value);
      return -1;
    }
    return 0;
  }

  if (strcasecmp(key, "Instances") == 0) {
    char *eptr = NULL;
    double val = strtod(value, &eptr);

    if (*eptr != '\0') {
      ERROR(PLUGIN_NAME " plugin: Invalid value for Instances = '%s'", value);
      return 1;
    }
    if (val <= 0) {
      ERROR(PLUGIN_NAME " plugin: Instances <= 0 makes no sense.");
      return 1;
    }
    if (val > NR_INSTANCES_MAX) {
      ERROR(PLUGIN_NAME " plugin: Instances=%f > NR_INSTANCES_MAX=%i"
                        " use a lower setting or recompile the plugin.",
            val, NR_INSTANCES_MAX);
      return 1;
    }

    nr_instances = (int)val;
    DEBUG(PLUGIN_NAME " plugin: configured %i instances", nr_instances);
    return 0;
  }

  if (strcasecmp(key, "ExtraStats") == 0) {
    char *localvalue = strdup(value);
    if (localvalue != NULL) {
      char *exstats[EX_STATS_MAX_FIELDS];
      int numexstats =
          strsplit(localvalue, exstats, STATIC_ARRAY_SIZE(exstats));
      extra_stats = parse_ex_stats_flags(exstats, numexstats);
      sfree(localvalue);

#ifdef HAVE_JOB_STATS
      if ((extra_stats & ex_stats_job_stats_completed) &&
          (extra_stats & ex_stats_job_stats_background)) {
        ERROR(PLUGIN_NAME " plugin: Invalid job stats configuration. Only one "
                          "type of job statistics can be collected at the same "
                          "time");
        return 1;
      }
#endif
    }
  }

  /* Unrecognised option. */
  return -1;
}