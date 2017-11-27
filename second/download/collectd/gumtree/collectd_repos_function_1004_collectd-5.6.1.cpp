void module_register (void)
{
	perl_argc = 4;
	perl_argv = smalloc ((perl_argc + 1) * sizeof (*perl_argv));

	/* default options for the Perl interpreter */
	perl_argv[0] = "";
	perl_argv[1] = "-MCollectd";
	perl_argv[2] = "-e";
	perl_argv[3] = "1";
	perl_argv[4] = NULL;

	plugin_register_complex_config ("perl", perl_config);
	return;
}