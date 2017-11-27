static int perl_shutdown (void)
{
	int ret = 0;

	plugin_unregister_complex_config ("perl");

	if (NULL == perl)
		return 0;

	plugin_unregister_log ("perl");
	plugin_unregister_init ("perl");
	plugin_unregister_read ("perl");
	plugin_unregister_write ("perl");

	PERL_SET_CONTEXT (perl);
	ret = pplugin_call_all (PLUGIN_SHUTDOWN);

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