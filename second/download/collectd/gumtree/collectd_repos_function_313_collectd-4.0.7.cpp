static void perl_log (int level, const char *msg)
{
	assert (NULL != perl);

	PERL_SET_CONTEXT (perl);
	pplugin_call_all (PLUGIN_LOG, level, msg);
	return;
}