static int init_pi (int argc, char **argv)
{
	if (NULL != perl)
		return 0;

	log_info ("Initializing Perl interpreter...");
#if COLLECT_DEBUG
	{
		int i = 0;

		for (i = 0; i < argc; ++i)
			log_debug ("argv[%i] = \"%s\"", i, argv[i]);
	}
#endif /* COLLECT_DEBUG */

	PERL_SYS_INIT3 (&argc, &argv, &environ);

	if (NULL == (perl = perl_alloc ())) {
		log_err ("module_register: Not enough memory.");
		exit (3);
	}
	perl_construct (perl);

	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

	if (0 != perl_parse (perl, xs_init, argc, argv, NULL)) {
		log_err ("module_register: Unable to bootstrap Collectd.");
		exit (1);
	}

	/* Set $0 to "collectd" because perl_parse() has to set it to "-e". */
	Perl_sv_setpv (perl, Perl_get_sv (perl, "0", 0), "collectd");

	perl_run (perl);

	plugin_register_log ("perl", perl_log);
	plugin_register_init ("perl", perl_init);

	plugin_register_read ("perl", perl_read);

	plugin_register_write ("perl", perl_write);
	plugin_register_shutdown ("perl", perl_shutdown);
	return 0;
}