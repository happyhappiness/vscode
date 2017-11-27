static int openvpn_config(const char *key, const char *value) {
  if (strcasecmp("StatusFile", key) == 0) {
    char callback_name[3 * DATA_MAX_NAME_LEN];
    char *status_name;

    char *status_file = strdup(value);
    if (status_file == NULL) {
      char errbuf[1024];
      ERROR("openvpn plugin: strdup failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      return 1;
    }

    /* it determines the file name as string starting at location filename + 1
     */
    char *filename = strrchr(status_file, (int)'/');
    if (filename == NULL) {
      /* status_file is already the file name only */
      status_name = status_file;
    } else {
      /* doesn't waste memory, uses status_file starting at filename + 1 */
      status_name = filename + 1;
    }

    /* create a new vpn element */
    vpn_status_t *instance = calloc(1, sizeof(*instance));
    if (instance == NULL) {
      char errbuf[1024];
      ERROR("openvpn plugin: malloc failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      sfree(status_file);
      return 1;
    }
    instance->file = status_file;
    instance->name = status_name;

    snprintf(callback_name, sizeof(callback_name), "openvpn/%s", status_name);

    int status = plugin_register_complex_read(
        /* group = */ "openvpn",
        /* name      = */ callback_name,
        /* callback  = */ openvpn_read,
        /* interval  = */ 0,
        &(user_data_t){
            .data = instance, .free_func = openvpn_free,
        });

    if (status == EINVAL) {
      WARNING("openvpn plugin: status filename \"%s\" "
              "already used, please choose a "
              "different one.",
              status_name);
      return -1;
    }

    DEBUG("openvpn plugin: status file \"%s\" added", instance->file);
  } /* if (strcasecmp ("StatusFile", key) == 0) */
  else if ((strcasecmp("CollectCompression", key) == 0) ||
           (strcasecmp("Compression", key) == 0)) /* old, deprecated name */
  {
    if (IS_FALSE(value))
      collect_compression = 0;
    else
      collect_compression = 1;
  } /* if (strcasecmp ("CollectCompression", key) == 0) */
  else if (strcasecmp("ImprovedNamingSchema", key) == 0) {
    if (IS_TRUE(value)) {
      DEBUG("openvpn plugin: using the new naming schema");
      new_naming_schema = 1;
    } else {
      new_naming_schema = 0;
    }
  } /* if (strcasecmp ("ImprovedNamingSchema", key) == 0) */
  else if (strcasecmp("CollectUserCount", key) == 0) {
    if (IS_TRUE(value))
      collect_user_count = 1;
    else
      collect_user_count = 0;
  } /* if (strcasecmp("CollectUserCount", key) == 0) */
  else if (strcasecmp("CollectIndividualUsers", key) == 0) {
    if (IS_FALSE(value))
      collect_individual_users = 0;
    else
      collect_individual_users = 1;
  } /* if (strcasecmp("CollectIndividualUsers", key) == 0) */
  else {
    return -1;
  }

  return 0;
}