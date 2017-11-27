static int perl_config_basename (pTHX_ oconfig_item_t *ci)
{
	char *value = NULL;

	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type)) {
		log_err ("BaseName expects a single string argument.");
		return 1;
	}

	value = ci->values[0].value.string;

	log_debug ("perl_config: Setting plugin basename to \"%s\"", value);
	sstrncpy (base_name, value, sizeof (base_name));
	return 0;
}