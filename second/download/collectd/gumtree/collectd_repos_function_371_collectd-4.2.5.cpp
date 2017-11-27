static int perl_read (void)
{
	if (NULL == perl)
		return 0;

	PERL_SET_CONTEXT (perl);
	return pplugin_call_all (PLUGIN_READ);
}