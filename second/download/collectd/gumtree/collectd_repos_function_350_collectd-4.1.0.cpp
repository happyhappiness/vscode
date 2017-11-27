static int perl_shutdown (void)
{
	int i   = 0;
	int ret = 0;

	plugin_unregister_log ("perl");
	plugin_unregister_config ("perl");
	plugin_unregister_init ("perl");
	plugin_unregister_read ("perl");
	plugin_unregister_write ("perl");

	assert (NULL != perl);

	PERL_SET_CONTEXT (perl);
	ret = pplugin_call_all (PLUGIN_SHUTDOWN);

	for (i = 0; i < PLUGIN_TYPES; ++i) {
		if (0 < Perl_hv_iterinit (perl, plugins[i])) {
			char *k = NULL;
			I32  l  = 0;

			while (NULL != Perl_hv_iternextsv (perl, plugins[i], &k, &l)) {
				pplugin_unregister (i, k);
			}
		}

		Perl_hv_undef (perl, plugins[i]);
	}

	if (0 < Perl_hv_iterinit (perl, data_sets)) {
		char *k = NULL;
		I32  l  = 0;

		while (NULL != Perl_hv_iternextsv (perl, data_sets, &k, &l)) {
			pplugin_unregister_data_set (k);
		}
	}

	Perl_hv_undef (perl, data_sets);

#if COLLECT_DEBUG
	Perl_sv_report_used (perl);
#endif /* COLLECT_DEBUG */

	perl_destruct (perl);
	perl_free (perl);
	perl = NULL;

	PERL_SYS_TERM ();

	plugin_unregister_shutdown ("perl");
	return ret;
}