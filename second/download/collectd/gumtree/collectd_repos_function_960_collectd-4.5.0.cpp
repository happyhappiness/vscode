static void submit_one (const char *plugin_instance, const char *type,
    const char *type_instance, value_t value)
{
  submit (plugin_instance, type, type_instance, &value, 1);
}