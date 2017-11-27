
	if (2 != items) {
		log_err ("Usage: Collectd::plugin_log(level, message)");
		XSRETURN_EMPTY;
	}

	plugin_log (SvIV (ST (0)), SvPV_nolen (ST (1)));
	XSRETURN_YES;
} /* static XS (Collectd_plugin_log) */

/*
 * Interface to collectd.
 */

static int perl_init (void)
{
	if (NULL == perl)
		return 0;

	PERL_SET_CONTEXT (perl);
	return pplugin_call_all (PLUGIN_INIT);
} /* static int perl_init (void) */

static int perl_read (void)
{
	if (NULL == perl)
		return 0;

	PERL_SET_CONTEXT (perl);
	return pplugin_call_all (PLUGIN_READ);
} /* static int perl_read (void) */

static int perl_write (const data_set_t *ds, const value_list_t *vl)
{
	if (NULL == perl)
		return 0;

	PERL_SET_CONTEXT (perl);
	return pplugin_call_all (PLUGIN_WRITE, ds, vl);
} /* static int perl_write (const data_set_t *, const value_list_t *) */

static void perl_log (int level, const char *msg)
{
	if (NULL == perl)
		return;

	PERL_SET_CONTEXT (perl);
	pplugin_call_all (PLUGIN_LOG, level, msg);
	return;
} /* static void perl_log (int, const char *) */

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
