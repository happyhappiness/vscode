
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
	perl = NULL;

	PERL_SYS_TERM ();

	plugin_unregister_shutdown ("perl");
	return ret;
} /* static void perl_shutdown (void) */

/* bootstrap the Collectd module */
static void xs_init (pTHX)
{
	HV   *stash = NULL;
	char *file  = __FILE__;

	int i = 0;

	dXSUB_SYS;

	/* enable usage of Perl modules using shared libraries */
	Perl_newXS (perl, "DynaLoader::boot_DynaLoader", boot_DynaLoader, file);

	/* register API */
	for (i = 0; NULL != api[i].f; ++i)
		Perl_newXS (perl, api[i].name, api[i].f, file);

	stash = Perl_gv_stashpv (perl, "Collectd", 1);

	/* export "constants" */
	for (i = 0; '\0' != constants[i].name[0]; ++i)
		Perl_newCONSTSUB (perl, stash, constants[i].name,
				Perl_newSViv (perl, constants[i].value));
	return;
} /* static void xs_init (pTHX) */

/* Initialize the global Perl interpreter. */
static int init_pi (int argc, char **argv)
{
	if (NULL != perl)
		return 0;

	log_info ("Initializing Perl interpreter...");
#if COLLECT_DEBUG
	{
		int i = 0;

		for (i = 0; i < argc; ++i)
			log_debug ("argv[%i] = \"%s\"", i, argv[i]);
	}
#endif /* COLLECT_DEBUG */

	PERL_SYS_INIT3 (&argc, &argv, &environ);

	if (NULL == (perl = perl_alloc ())) {
		log_err ("module_register: Not enough memory.");
		exit (3);
	}
	perl_construct (perl);

	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

	if (0 != perl_parse (perl, xs_init, argc, argv, NULL)) {
		log_err ("module_register: Unable to bootstrap Collectd.");
		exit (1);
	}

	/* Set $0 to "collectd" because perl_parse() has to set it to "-e". */
	Perl_sv_setpv (perl, Perl_get_sv (perl, "0", 0), "collectd");

	perl_run (perl);

	plugin_register_log ("perl", perl_log);
	plugin_register_init ("perl", perl_init);

	plugin_register_read ("perl", perl_read);

	plugin_register_write ("perl", perl_write);
	plugin_register_shutdown ("perl", perl_shutdown);
	return 0;
} /* static int init_pi (const char **, const int) */

/*
 * LoadPlugin "<Plugin>"
 */
static int perl_config_loadplugin (oconfig_item_t *ci)
{
	char module_name[DATA_MAX_NAME_LEN];

	char *value = NULL;

	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type))
		return 1;

	value = ci->values[0].value.string;

	if (NULL == get_module_name (module_name, sizeof (module_name), value)) {
		log_err ("Invalid module name %s", value);
		return (1);
	}

	init_pi (perl_argc, perl_argv);

	log_debug ("perl_config: loading perl plugin \"%s\"", value);
	Perl_load_module (perl, PERL_LOADMOD_NOIMPORT,
			Perl_newSVpv (perl, module_name, strlen (module_name)),
			Nullsv);
	return 0;
} /* static int perl_config_loadplugin (oconfig_item_it *) */

/*
 * BaseName "<Name>"
 */
static int perl_config_basename (oconfig_item_t *ci)
{
	char *value = NULL;

	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type))
		return 1;

	value = ci->values[0].value.string;

	log_debug ("perl_config: Setting plugin basename to \"%s\"", value);
	strncpy (base_name, value, sizeof (base_name));
	base_name[sizeof (base_name) - 1] = '\0';
	return 0;
} /* static int perl_config_basename (oconfig_item_it *) */

/*
 * EnableDebugger "<Package>"|""
 */
static int perl_config_enabledebugger (oconfig_item_t *ci)
{
	char *value = NULL;

	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type))
		return 1;

	value = ci->values[0].value.string;

	perl_argv = (char **)realloc (perl_argv,
			(++perl_argc + 1) * sizeof (char *));

