static int perl_write (const data_set_t *ds, const value_list_t *vl)
{
	assert (NULL != perl);

	PERL_SET_CONTEXT (perl);
	return pplugin_call_all (PLUGIN_WRITE, ds, vl);
}