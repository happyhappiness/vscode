static int perl_config_basename (oconfig_item_t *ci)
{
	char *value = NULL;

	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type))
		return 1;

	value = ci->values[0].value.string;

	log_debug ("perl_config: Setting plugin basename to \"%s\"", value);
	strncpy (base_name, value, sizeof (base_name));
	base_name[sizeof (base_name) - 1] = '\0';
	return 0;
}