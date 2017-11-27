static int perl_config_loadplugin (oconfig_item_t *ci)
{
	char module_name[DATA_MAX_NAME_LEN];

	char *value = NULL;

	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type))
		return 1;

	value = ci->values[0].value.string;

	if (NULL == get_module_name (module_name, sizeof (module_name), value)) {
		log_err ("Invalid module name %s", value);
		return (1);
	}

	init_pi (perl_argc, perl_argv);

	log_debug ("perl_config: loading perl plugin \"%s\"", value);
	Perl_load_module (perl, PERL_LOADMOD_NOIMPORT,
			Perl_newSVpv (perl, module_name, strlen (module_name)),
			Nullsv);
	return 0;
}