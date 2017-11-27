static int cow_read_values(const char *path, const char *name,
                           const ow_family_features_t *family_info) {
  value_list_t vl = VALUE_LIST_INIT;
  int success = 0;

  if (sensor_list != NULL) {
    DEBUG("onewire plugin: Checking ignorelist for `%s'", name);
    if (ignorelist_match(sensor_list, name) != 0)
      return 0;
  }

  sstrncpy(vl.plugin, "onewire", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, name, sizeof(vl.plugin_instance));

  for (size_t i = 0; i < family_info->features_num; i++) {
    char *buffer;
    size_t buffer_size;
    int status;
    char errbuf[1024];

    char file[4096];
    char *endptr;

    snprintf(file, sizeof(file), "%s/%s", path,
             family_info->features[i].filename);
    file[sizeof(file) - 1] = 0;

    buffer = NULL;
    buffer_size = 0;
    DEBUG("Start reading onewire device %s", file);
    status = OW_get(file, &buffer, &buffer_size);
    if (status < 0) {
      ERROR("onewire plugin: OW_get (%s/%s) failed. error = %s;", path,
            family_info->features[i].filename,
            sstrerror(errno, errbuf, sizeof(errbuf)));
      return (-1);
    }
    DEBUG("Read onewire device %s as %s", file, buffer);

    endptr = NULL;
    gauge_t g = strtod(buffer, &endptr);
    if (endptr == NULL) {
      ERROR("onewire plugin: Buffer is not a number: %s", buffer);
      continue;
    }

    sstrncpy(vl.type, family_info->features[i].type, sizeof(vl.type));
    sstrncpy(vl.type_instance, family_info->features[i].type_instance,
             sizeof(vl.type_instance));

    vl.values = &(value_t){.gauge = g};
    vl.values_len = 1;

    plugin_dispatch_values(&vl);
    success++;

    free(buffer);
  } /* for (i = 0; i < features_num; i++) */

  return ((success > 0) ? 0 : -1);
}