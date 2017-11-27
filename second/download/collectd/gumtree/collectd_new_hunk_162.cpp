
	plugin_log (SvIV (ST (0)), SvPV_nolen (ST (1)));
	XSRETURN_YES;
} /* static XS (Collectd_plugin_log) */

/*
 * Collectd::call_by_name (...).
 *
 * Call a Perl sub identified by its name passed through $Collectd::cb_name.
 */
static XS (Collectd_call_by_name)
{
	SV   *tmp  = NULL;
	char *name = NULL;

	if (NULL == (tmp = get_sv ("Collectd::cb_name", 0))) {
		sv_setpv (get_sv ("@", 1), "cb_name has not been set");
		CLEAR_STACK_FRAME;
		return;
	}

	name = SvPV_nolen (tmp);

	if (NULL == get_cv (name, 0)) {
		sv_setpvf (get_sv ("@", 1), "unknown callback \"%s\"", name);
		CLEAR_STACK_FRAME;
		return;
	}

	/* simply pass on the subroutine call without touching the stack,
	 * thus leaving any arguments and return values in place */
	call_pv (name, 0);
} /* static XS (Collectd_call_by_name) */

/*
 * collectd's perl interpreter based thread implementation.
 *
 * This has been inspired by Perl's ithreads introduced in version 5.6.0.
 */

/* must be called with perl_threads->mutex locked */
static void c_ithread_destroy (c_ithread_t *ithread)
{
	dTHXa (ithread->interp);

	assert (NULL != perl_threads);

	PERL_SET_CONTEXT (aTHX);
	log_debug ("Shutting down Perl interpreter %p...", aTHX);

#if COLLECT_DEBUG
	sv_report_used ();

	--perl_threads->number_of_threads;
#endif /* COLLECT_DEBUG */

	perl_destruct (aTHX);
	perl_free (aTHX);

	if (NULL == ithread->prev)
		perl_threads->head = ithread->next;
	else
		ithread->prev->next = ithread->next;

	if (NULL == ithread->next)
		perl_threads->tail = ithread->prev;
	else
		ithread->next->prev = ithread->prev;

	sfree (ithread);
	return;
} /* static void c_ithread_destroy (c_ithread_t *) */

static void c_ithread_destructor (void *arg)
{
	c_ithread_t *ithread = (c_ithread_t *)arg;
	c_ithread_t *t = NULL;

	if (NULL == perl_threads)
		return;

	pthread_mutex_lock (&perl_threads->mutex);

	for (t = perl_threads->head; NULL != t; t = t->next)
		if (t == ithread)
			break;

	/* the ithread no longer exists */
	if (NULL == t)
		return;

	c_ithread_destroy (ithread);

	pthread_mutex_unlock (&perl_threads->mutex);
	return;
} /* static void c_ithread_destructor (void *) */

/* must be called with perl_threads->mutex locked */
static c_ithread_t *c_ithread_create (PerlInterpreter *base)
{
	c_ithread_t *t = NULL;
	dTHXa (NULL);

	assert (NULL != perl_threads);

	t = (c_ithread_t *)smalloc (sizeof (c_ithread_t));
	memset (t, 0, sizeof (c_ithread_t));

	t->interp = (NULL == base)
		? NULL
		: perl_clone (base, CLONEf_KEEP_PTR_TABLE);

	aTHX = t->interp;

	if (NULL != base) {
		av_clear (PL_endav);
		av_undef (PL_endav);
		PL_endav = Nullav;
	}

#if COLLECT_DEBUG
	++perl_threads->number_of_threads;
#endif /* COLLECT_DEBUG */

	t->next = NULL;

	if (NULL == perl_threads->tail) {
		perl_threads->head = t;
		t->prev = NULL;
	}
	else {
		perl_threads->tail->next = t;
		t->prev = perl_threads->tail;
	}

	perl_threads->tail = t;

	pthread_setspecific (perl_thr_key, (const void *)t);
	return t;
} /* static c_ithread_t *c_ithread_create (PerlInterpreter *) */

/*
 * Interface to collectd.
 */

static int perl_init (void)
{
	dTHX;

	if (NULL == perl_threads)
		return 0;

	if (NULL == aTHX) {
		c_ithread_t *t = NULL;

		pthread_mutex_lock (&perl_threads->mutex);
		t = c_ithread_create (perl_threads->head->interp);
		pthread_mutex_unlock (&perl_threads->mutex);

		aTHX = t->interp;
	}

	log_debug ("perl_init: c_ithread: interp = %p (active threads: %i)",
			aTHX, perl_threads->number_of_threads);
	return pplugin_call_all (aTHX_ PLUGIN_INIT);
} /* static int perl_init (void) */

static int perl_read (void)
{
	dTHX;

	if (NULL == perl_threads)
		return 0;

	if (NULL == aTHX) {
		c_ithread_t *t = NULL;

		pthread_mutex_lock (&perl_threads->mutex);
		t = c_ithread_create (perl_threads->head->interp);
		pthread_mutex_unlock (&perl_threads->mutex);

		aTHX = t->interp;
	}

	log_debug ("perl_read: c_ithread: interp = %p (active threads: %i)",
			aTHX, perl_threads->number_of_threads);
	return pplugin_call_all (aTHX_ PLUGIN_READ);
} /* static int perl_read (void) */

static int perl_write (const data_set_t *ds, const value_list_t *vl)
{
	dTHX;

	if (NULL == perl_threads)
		return 0;

	if (NULL == aTHX) {
		c_ithread_t *t = NULL;

		pthread_mutex_lock (&perl_threads->mutex);
		t = c_ithread_create (perl_threads->head->interp);
		pthread_mutex_unlock (&perl_threads->mutex);

		aTHX = t->interp;
	}

	log_debug ("perl_write: c_ithread: interp = %p (active threads: %i)",
			aTHX, perl_threads->number_of_threads);
	return pplugin_call_all (aTHX_ PLUGIN_WRITE, ds, vl);
} /* static int perl_write (const data_set_t *, const value_list_t *) */

static void perl_log (int level, const char *msg)
{
	dTHX;

	if (NULL == perl_threads)
		return;

	if (NULL == aTHX) {
		c_ithread_t *t = NULL;

		pthread_mutex_lock (&perl_threads->mutex);
		t = c_ithread_create (perl_threads->head->interp);
		pthread_mutex_unlock (&perl_threads->mutex);

		aTHX = t->interp;
	}

	pplugin_call_all (aTHX_ PLUGIN_LOG, level, msg);
	return;
} /* static void perl_log (int, const char *) */

static int perl_notify (const notification_t *notif)
{
	dTHX;

	if (NULL == perl_threads)
		return 0;

	if (NULL == aTHX) {
		c_ithread_t *t = NULL;

		pthread_mutex_lock (&perl_threads->mutex);
		t = c_ithread_create (perl_threads->head->interp);
		pthread_mutex_unlock (&perl_threads->mutex);

		aTHX = t->interp;
	}
	return pplugin_call_all (aTHX_ PLUGIN_NOTIF, notif);
} /* static int perl_notify (const notification_t *) */

static int perl_shutdown (void)
{
	c_ithread_t *t = NULL;

	int ret = 0;

	dTHX;

	plugin_unregister_complex_config ("perl");

	if (NULL == perl_threads)
		return 0;

	if (NULL == aTHX) {
		c_ithread_t *t = NULL;

		pthread_mutex_lock (&perl_threads->mutex);
		t = c_ithread_create (perl_threads->head->interp);
		pthread_mutex_unlock (&perl_threads->mutex);

		aTHX = t->interp;
	}

	log_debug ("perl_shutdown: c_ithread: interp = %p (active threads: %i)",
			aTHX, perl_threads->number_of_threads);

	plugin_unregister_log ("perl");
	plugin_unregister_notification ("perl");
	plugin_unregister_init ("perl");
	plugin_unregister_read ("perl");
	plugin_unregister_write ("perl");

	ret = pplugin_call_all (aTHX_ PLUGIN_SHUTDOWN);

	pthread_mutex_lock (&perl_threads->mutex);
	t = perl_threads->tail;

	while (NULL != t) {
		c_ithread_t *thr = t;

		/* the pointer has to be advanced before destroying
		 * the thread as this will free the memory */
		t = t->prev;

		c_ithread_destroy (thr);
	}

	pthread_mutex_unlock (&perl_threads->mutex);
	pthread_mutex_destroy (&perl_threads->mutex);

	sfree (perl_threads);

	pthread_key_delete (perl_thr_key);

	PERL_SYS_TERM ();

	plugin_unregister_shutdown ("perl");
	return ret;
} /* static void perl_shutdown (void) */

/*
 * Access functions for global variables.
 *
 * These functions implement the "magic" used to access
 * the global variables from Perl.
 */

static int g_pv_get (pTHX_ SV *var, MAGIC *mg)
{
	char *pv = mg->mg_ptr;
	sv_setpv (var, pv);
	return 0;
} /* static int g_pv_get (pTHX_ SV *, MAGIC *) */

static int g_pv_set (pTHX_ SV *var, MAGIC *mg)
{
	char *pv = mg->mg_ptr;
	strncpy (pv, SvPV_nolen (var), DATA_MAX_NAME_LEN);
	pv[DATA_MAX_NAME_LEN - 1] = '\0';
	return 0;
} /* static int g_pv_set (pTHX_ SV *, MAGIC *) */

static int g_iv_get (pTHX_ SV *var, MAGIC *mg)
{
	int *iv = (int *)mg->mg_ptr;
	sv_setiv (var, *iv);
	return 0;
} /* static int g_iv_get (pTHX_ SV *, MAGIC *) */

static int g_iv_set (pTHX_ SV *var, MAGIC *mg)
{
	int *iv = (int *)mg->mg_ptr;
	*iv = (int)SvIV (var);
	return 0;
} /* static int g_iv_set (pTHX_ SV *, MAGIC *) */

static MGVTBL g_pv_vtbl = { g_pv_get, g_pv_set, NULL, NULL, NULL, NULL, NULL };
static MGVTBL g_iv_vtbl = { g_iv_get, g_iv_set, NULL, NULL, NULL, NULL, NULL };

/* bootstrap the Collectd module */
static void xs_init (pTHX)
{
	HV   *stash = NULL;
	SV   *tmp   = NULL;
	char *file  = __FILE__;

	int i = 0;

	dXSUB_SYS;

	/* enable usage of Perl modules using shared libraries */
	newXS ("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);

	/* register API */
	for (i = 0; NULL != api[i].f; ++i)
		newXS (api[i].name, api[i].f, file);

	stash = gv_stashpv ("Collectd", 1);

	/* export "constants" */
	for (i = 0; '\0' != constants[i].name[0]; ++i)
		newCONSTSUB (stash, constants[i].name, newSViv (constants[i].value));

	/* export global variables
	 * by adding "magic" to the SV's representing the globale variables
	 * perl is able to automagically call the get/set function when
	 * accessing any such variable (this is basically the same as using
	 * tie() in Perl) */
	/* global strings */
	for (i = 0; '\0' != g_strings[i].name[0]; ++i) {
		tmp = get_sv (g_strings[i].name, 1);
		sv_magicext (tmp, NULL, PERL_MAGIC_ext, &g_pv_vtbl,
				g_strings[i].var, 0);
	}

	/* global integers */
	for (i = 0; '\0' != g_integers[i].name[0]; ++i) {
		tmp = get_sv (g_integers[i].name, 1);
		sv_magicext (tmp, NULL, PERL_MAGIC_ext, &g_iv_vtbl,
				(char *)g_integers[i].var, 0);
	}
	return;
} /* static void xs_init (pTHX) */

/* Initialize the global Perl interpreter. */
static int init_pi (int argc, char **argv)
{
	dTHXa (NULL);

	if (NULL != perl_threads)
		return 0;

	log_info ("Initializing Perl interpreter...");
#if COLLECT_DEBUG
	{
		int i = 0;

		for (i = 0; i < argc; ++i)
			log_debug ("argv[%i] = \"%s\"", i, argv[i]);
	}
#endif /* COLLECT_DEBUG */

	if (0 != pthread_key_create (&perl_thr_key, c_ithread_destructor)) {
		log_err ("init_pi: pthread_key_create failed");

		/* this must not happen - cowardly giving up if it does */
		exit (1);
	}

	PERL_SYS_INIT3 (&argc, &argv, &environ);

	perl_threads = (c_ithread_list_t *)smalloc (sizeof (c_ithread_list_t));
	memset (perl_threads, 0, sizeof (c_ithread_list_t));

	pthread_mutex_init (&perl_threads->mutex, NULL);
	/* locking the mutex should not be necessary at this point
	 * but let's just do it for the sake of completeness */
	pthread_mutex_lock (&perl_threads->mutex);

	perl_threads->head = c_ithread_create (NULL);
	perl_threads->tail = perl_threads->head;

	if (NULL == (perl_threads->head->interp = perl_alloc ())) {
		log_err ("init_pi: Not enough memory.");
		exit (3);
	}

	aTHX = perl_threads->head->interp;
	pthread_mutex_unlock (&perl_threads->mutex);

	perl_construct (aTHX);

	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

	if (0 != perl_parse (aTHX_ xs_init, argc, argv, NULL)) {
		log_err ("init_pi: Unable to bootstrap Collectd.");
		exit (1);
	}

	/* Set $0 to "collectd" because perl_parse() has to set it to "-e". */
	sv_setpv (get_sv ("0", 0), "collectd");

	perl_run (aTHX);

	plugin_register_log ("perl", perl_log);
	plugin_register_notification ("perl", perl_notify);
	plugin_register_init ("perl", perl_init);

	plugin_register_read ("perl", perl_read);

	plugin_register_write ("perl", perl_write);
	plugin_register_shutdown ("perl", perl_shutdown);
	return 0;
} /* static int init_pi (const char **, const int) */

/*
 * LoadPlugin "<Plugin>"
 */
static int perl_config_loadplugin (pTHX_ oconfig_item_t *ci)
{
	char module_name[DATA_MAX_NAME_LEN];

	char *value = NULL;

	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type)) {
		log_err ("LoadPlugin expects a single string argument.");
		return 1;
	}

	value = ci->values[0].value.string;

	if (NULL == get_module_name (module_name, sizeof (module_name), value)) {
		log_err ("Invalid module name %s", value);
		return (1);
	}

	init_pi (perl_argc, perl_argv);
	assert (NULL != perl_threads);
	assert (NULL != perl_threads->head);

	aTHX = perl_threads->head->interp;

	log_debug ("perl_config: loading perl plugin \"%s\"", value);
	load_module (PERL_LOADMOD_NOIMPORT,
			newSVpv (module_name, strlen (module_name)), Nullsv);
	return 0;
} /* static int perl_config_loadplugin (oconfig_item_it *) */

/*
 * BaseName "<Name>"
 */
static int perl_config_basename (pTHX_ oconfig_item_t *ci)
{
	char *value = NULL;

	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type)) {
		log_err ("BaseName expects a single string argument.");
		return 1;
	}

	value = ci->values[0].value.string;

	log_debug ("perl_config: Setting plugin basename to \"%s\"", value);
	strncpy (base_name, value, sizeof (base_name));
	base_name[sizeof (base_name) - 1] = '\0';
	return 0;
} /* static int perl_config_basename (oconfig_item_it *) */

/*
 * EnableDebugger "<Package>"|""
 */
static int perl_config_enabledebugger (pTHX_ oconfig_item_t *ci)
{
	char *value = NULL;

	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type)) {
		log_err ("EnableDebugger expects a single string argument.");
		return 1;
	}

	value = ci->values[0].value.string;

	perl_argv = (char **)realloc (perl_argv,
			(++perl_argc + 1) * sizeof (char *));

