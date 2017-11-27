void module_register(void) {
  plugin_register_complex_config("aggregation", agg_config);
  plugin_register_read("aggregation", agg_read);
  plugin_register_write("aggregation", agg_write, /* user_data = */ NULL);
}