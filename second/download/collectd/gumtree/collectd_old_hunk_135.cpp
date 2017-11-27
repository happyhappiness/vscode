
	if (2 != items) {
		log_err ("Usage: Collectd::plugin_log(level, message)");
		XSRETURN_EMPTY;
	}

	log_debug ("Collectd::plugin_log: level = %i, message = \"%s\"",
			SvIV (ST (0)), SvPV_nolen (ST (1)));
	plugin_log (SvIV (ST (0)), SvPV_nolen (ST (1)));
	XSRETURN_YES;
} /* static XS (Collectd_plugin_log) */

/*
 * Collectd::bootstrap ().
 */
static XS (boot_Collectd)
{
	HV   *stash = NULL;
	char *file  = __FILE__;

	struct {
		char name[64];
		SV   *value;
	} consts[] =
	{
		{ "Collectd::TYPE_INIT",       Perl_newSViv (perl, PLUGIN_INIT) },
		{ "Collectd::TYPE_READ",       Perl_newSViv (perl, PLUGIN_READ) },
		{ "Collectd::TYPE_WRITE",      Perl_newSViv (perl, PLUGIN_WRITE) },
		{ "Collectd::TYPE_SHUTDOWN",   Perl_newSViv (perl, PLUGIN_SHUTDOWN) },
		{ "Collectd::TYPE_LOG",        Perl_newSViv (perl, PLUGIN_LOG) },
		{ "Collectd::TYPE_DATASET",    Perl_newSViv (perl, PLUGIN_DATASET) },
		{ "Collectd::DS_TYPE_COUNTER", Perl_newSViv (perl, DS_TYPE_COUNTER) },
		{ "Collectd::DS_TYPE_GAUGE",   Perl_newSViv (perl, DS_TYPE_GAUGE) },
		{ "Collectd::LOG_ERR",         Perl_newSViv (perl, LOG_ERR) },
		{ "Collectd::LOG_WARNING",     Perl_newSViv (perl, LOG_WARNING) },
		{ "Collectd::LOG_NOTICE",      Perl_newSViv (perl, LOG_NOTICE) },
		{ "Collectd::LOG_INFO",        Perl_newSViv (perl, LOG_INFO) },
		{ "Collectd::LOG_DEBUG",       Perl_newSViv (perl, LOG_DEBUG) },
		{ "", NULL }
	};

	int i = 0;

	dXSARGS;

	if ((1 > items) || (2 < items)) {
		log_err ("Usage: Collectd::bootstrap(name[, version])");
		XSRETURN_EMPTY;
	}

	XS_VERSION_BOOTCHECK;

	/* register API */
	for (i = 0; NULL != api[i].f; ++i)
		Perl_newXS (perl, api[i].name, api[i].f, file);

	stash = Perl_gv_stashpv (perl, "Collectd", 1);

	/* export "constants" */
	for (i = 0; NULL != consts[i].value; ++i)
		Perl_newCONSTSUB (perl, stash, consts[i].name, consts[i].value);
	XSRETURN_YES;
} /* static XS (boot_Collectd) */


/*
 * Interface to collectd.
 */

static int perl_config (const char *key, const char *value)
{
	assert (NULL != perl);

	log_debug ("perl_config: key = \"%s\", value=\"%s\"", key, value);

	if (0 == strcasecmp (key, "LoadPlugin")) {
		char module_name[DATA_MAX_NAME_LEN];

		if (get_module_name (module_name, sizeof (module_name), value)
				== NULL) {
			log_err ("Invalid module name %s", value);
			return (1);
		} /* if (get_module_name == NULL) */

		log_debug ("perl_config: loading perl plugin \"%s\"", value);
		Perl_load_module (perl, PERL_LOADMOD_NOIMPORT,
				Perl_newSVpv (perl, module_name, strlen (module_name)),
				Nullsv);
	}
	else if (0 == strcasecmp (key, "BaseName")) {
		log_debug ("perl_config: Setting plugin basename to \"%s\"", value);
		strncpy (base_name, value, sizeof (base_name));
		base_name[sizeof (base_name) - 1] = '\0';
	}
	else if (0 == strcasecmp (key, "IncludeDir")) {
		Perl_av_unshift (perl, GvAVn (PL_incgv), 1);
		Perl_av_store (perl, GvAVn (PL_incgv),
				0, Perl_newSVpv (perl, value, strlen (value)));
	}
	else {
		return -1;
	}
	return 0;
} /* static int perl_config (char *, char *) */

static int perl_init (void)
{
	assert (NULL != perl);

	PERL_SET_CONTEXT (perl);
	return pplugin_call_all (PLUGIN_INIT);
} /* static int perl_init (void) */

static int perl_read (void)
{
	assert (NULL != perl);

	PERL_SET_CONTEXT (perl);
	return pplugin_call_all (PLUGIN_READ);
} /* static int perl_read (void) */

static int perl_write (const data_set_t *ds, const value_list_t *vl)
{
	assert (NULL != perl);

	PERL_SET_CONTEXT (perl);
	return pplugin_call_all (PLUGIN_WRITE, ds, vl);
} /* static int perl_write (const data_set_t *, const value_list_t *) */

static void perl_log (int level, const char *msg)
{
	assert (NULL != perl);

	PERL_SET_CONTEXT (perl);
	pplugin_call_all (PLUGIN_LOG, level, msg);
	return;
} /* static void perl_log (int, const char *) */

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
