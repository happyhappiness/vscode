static int perl_config_enabledebugger (oconfig_item_t *ci)
{
	char *value = NULL;

	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type))
		return 1;

	value = ci->values[0].value.string;

	perl_argv = (char **)realloc (perl_argv,
			(++perl_argc + 1) * sizeof (char *));

	if (NULL == perl_argv) {
		log_err ("perl_config: Not enough memory.");
		exit (3);
	}

	if ('\0' == value[0]) {
		perl_argv[perl_argc - 1] = "-d";
	}
	else {
		perl_argv[perl_argc - 1] = (char *)smalloc (strlen (value) + 4);
		sstrncpy (perl_argv[perl_argc - 1], "-d:", 4);
		sstrncpy (perl_argv[perl_argc - 1] + 3, value, strlen (value) + 1);
	}

	perl_argv[perl_argc] = NULL;
	return 0;
}