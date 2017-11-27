void module_register (void)
{
	char *embed_argv[] = { "", "-e", "bootstrap Collectd \""VERSION"\"", NULL };
	int  embed_argc    = 3;

	int i = 0;

	log_debug ("module_register: Registering perl plugin...");

	PERL_SYS_INIT3 (&argc, &argv, &environ);

	if (NULL == (perl = perl_alloc ())) {
		log_err ("module_register: Not enough memory.");
		exit (3);
	}
	perl_construct (perl);

	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

	if (0 != perl_parse (perl, xs_init, embed_argc, embed_argv, NULL)) {
		log_err ("module_register: Unable to bootstrap Collectd.");
		exit (1);
	}
	perl_run (perl);

	for (i = 0; i < PLUGIN_TYPES; ++i)
		plugins[i] = Perl_newHV (perl);

	data_sets = Perl_newHV (perl);

	plugin_register_log ("perl", perl_log);
	plugin_register_config ("perl", perl_config, config_keys, config_keys_num);
	plugin_register_init ("perl", perl_init);

	plugin_register_read ("perl", perl_read);

	plugin_register_write ("perl", perl_write);
	plugin_register_shutdown ("perl", perl_shutdown);
	return;
}