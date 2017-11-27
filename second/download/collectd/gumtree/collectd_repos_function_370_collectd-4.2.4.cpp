static int perl_write (const data_set_t *ds, const value_list_t *vl)
{
	if (NULL == perl)
		return 0;

	PERL_SET_CONTEXT (perl);
	return pplugin_call_all (PLUGIN_WRITE, ds, vl);
}