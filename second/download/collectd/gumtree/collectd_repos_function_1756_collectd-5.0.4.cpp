static void submit_two (const char *plugin_instance, const char *type,
    const char *type_instance, derive_t c0, derive_t c1)
{
  value_t values[2];

  values[0].derive = c0;
  values[1].derive = c1;

  submit (plugin_instance, type, type_instance, values, 2);
}