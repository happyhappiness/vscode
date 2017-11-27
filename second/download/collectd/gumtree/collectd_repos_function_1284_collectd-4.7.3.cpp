static void submit_two (const char *plugin_instance, const char *type,
    const char *type_instance, counter_t c0, counter_t c1)
{
  value_t values[2];

  values[0].counter = c0;
  values[1].counter = c1;

  submit (plugin_instance, type, type_instance, values, 2);
}