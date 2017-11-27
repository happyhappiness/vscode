static int my_write(const data_set_t *ds, const value_list_t *vl,
                    user_data_t *ud) {
  char name[1024] = "";
  int i = 0;

  if (ds->ds_num != vl->values_len) {
    plugin_log(LOG_WARNING, "DS number does not match values length");
    return -1;
  }

  /* get the default base filename for the output file - depending on the
   * provided values this will be something like
   * <host>/<plugin>[-<plugin_type>]/<instance>[-<instance_type>] */
  if (0 != format_name(name, 1024, vl->host, vl->plugin, vl->plugin_instance,
                       ds->type, vl->type_instance))
    return -1;

  for (i = 0; i < ds->ds_num; ++i) {
    /* do the magic to output the data */
    printf("%s (%s) at %i: ", name,
           (ds->ds->type == DS_TYPE_GAUGE) ? "GAUGE" : "COUNTER",
           (int)vl->time);

    if (ds->ds->type == DS_TYPE_GAUGE)
      printf("%f\n", vl->values[i].gauge);
    else
      printf("%lld\n", vl->values[i].counter);
  }
  return 0;
}