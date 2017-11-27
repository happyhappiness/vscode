static int perl_read (void)
{
	assert (NULL != perl);

	PERL_SET_CONTEXT (perl);
	return pplugin_call_all (PLUGIN_READ);
}