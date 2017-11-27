static int my_submit(gauge_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  /* Convert the gauge_t to a value_t and add it to the value_list_t. */
  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;

  /* Only set vl.time yourself if you update multiple metrics (i.e. you
   * have multiple calls to plugin_dispatch_values()) and they need to all
   * have the same timestamp. */
  /* vl.time = cdtime(); */

  sstrncpy(vl.plugin, "myplugin", sizeof(vl.plugin));

  /* it is strongly recommended to use a type defined in the types.db file
   * instead of a custom type */
  sstrncpy(vl.type, "myplugin", sizeof(vl.type));
  /* optionally set vl.plugin_instance and vl.type_instance to reasonable
   * values (default: "") */

  /* dispatch the values to collectd which passes them on to all registered
   * write functions */
  return plugin_dispatch_values(&vl);
}