static int nut_add_ups(const char *name) {
  nut_ups_t *ups;
  int status;
  char *cb_name;

  DEBUG("nut plugin: nut_add_ups (name = %s);", name);

  ups = calloc(1, sizeof(*ups));
  if (ups == NULL) {
    ERROR("nut plugin: nut_add_ups: calloc failed.");
    return 1;
  }

  status = upscli_splitname(name, &ups->upsname, &ups->hostname, &ups->port);
  if (status != 0) {
    ERROR("nut plugin: nut_add_ups: upscli_splitname (%s) failed.", name);
    free_nut_ups_t(ups);
    return 1;
  }

  cb_name = ssnprintf_alloc("nut/%s", name);

  status = plugin_register_complex_read(
      /* group     = */ "nut",
      /* name      = */ cb_name,
      /* callback  = */ nut_read,
      /* interval  = */ 0,
      /* user_data = */ &(user_data_t){
          .data = ups, .free_func = free_nut_ups_t,
      });

  sfree(cb_name);

  if (status == EINVAL) {
    WARNING("nut plugin: UPS \"%s\" already added. "
            "Please check your configuration.",
            name);
    return -1;
  }

  return 0;
}