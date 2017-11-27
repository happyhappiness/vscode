static int perl_init (void)
{
	if (NULL == perl)
		return 0;

	PERL_SET_CONTEXT (perl);
	return pplugin_call_all (PLUGIN_INIT);
}