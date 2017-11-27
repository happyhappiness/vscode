static int perl_init (void)
{
	assert (NULL != perl);

	PERL_SET_CONTEXT (perl);
	return pplugin_call_all (PLUGIN_INIT);
}