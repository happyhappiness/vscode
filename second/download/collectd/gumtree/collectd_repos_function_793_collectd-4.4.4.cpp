static int ut_config_plugin_instance (threshold_t *th, oconfig_item_t *ci)
{
  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("threshold values: The `Instance' option needs exactly one "
	"string argument.");
    return (-1);
  }

  strncpy (th->plugin_instance, ci->values[0].value.string,
      sizeof (th->plugin_instance));
  th->plugin_instance[sizeof (th->plugin_instance) - 1] = '\0';

  return (0);
}