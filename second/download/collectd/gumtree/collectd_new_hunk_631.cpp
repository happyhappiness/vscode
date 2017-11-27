 * timeout:
 *   timeout to use when flushing the data
 *
 * identifier:
 *   data-set identifier to flush
 */
static XS(Collectd__plugin_flush) {
  char *plugin = NULL;
  int timeout = -1;
  char *id = NULL;

  dXSARGS;

  if (3 != items) {
    log_err("Usage: Collectd::_plugin_flush(plugin, timeout, id)");
    XSRETURN_EMPTY;
  }

  if (SvOK(ST(0)))
    plugin = SvPV_nolen(ST(0));

  if (SvOK(ST(1)))
    timeout = (int)SvIV(ST(1));

  if (SvOK(ST(2)))
    id = SvPV_nolen(ST(2));

  log_debug("Collectd::_plugin_flush: plugin = \"%s\", timeout = %i, "
            "id = \"%s\"",
            plugin, timeout, id);

  if (0 == plugin_flush(plugin, timeout, id))
    XSRETURN_YES;
  else
    XSRETURN_EMPTY;
} /* static XS (Collectd__plugin_flush) */

/*
 * Collectd::plugin_dispatch_notification (notif).
 *
 * notif:
 *   notification to dispatch
 */
static XS(Collectd_plugin_dispatch_notification) {
  SV *notif = NULL;

  int ret = 0;

  dXSARGS;

  if (1 != items) {
    log_err("Usage: Collectd::plugin_dispatch_notification(notif)");
    XSRETURN_EMPTY;
  }

  log_debug("Collectd::plugin_dispatch_notification: notif = \"%s\"",
            SvPV_nolen(ST(0)));

  notif = ST(0);

  if (!(SvROK(notif) && (SVt_PVHV == SvTYPE(SvRV(notif))))) {
    log_err("Collectd::plugin_dispatch_notification: Invalid notif.");
    XSRETURN_EMPTY;
  }

  ret = pplugin_dispatch_notification(aTHX_(HV *) SvRV(notif));

  if (0 == ret)
    XSRETURN_YES;
  else
    XSRETURN_EMPTY;
} /* static XS (Collectd_plugin_dispatch_notification) */

/*
 * Collectd::plugin_log (level, message).
 *
 * level:
 *   log level (LOG_DEBUG, ... LOG_ERR)
 *
 * message:
 *   log message
 */
static XS(Collectd_plugin_log) {
  dXSARGS;

  if (2 != items) {
    log_err("Usage: Collectd::plugin_log(level, message)");
    XSRETURN_EMPTY;
  }

  plugin_log(SvIV(ST(0)), "%s", SvPV_nolen(ST(1)));
  XSRETURN_YES;
} /* static XS (Collectd_plugin_log) */

/*
 * Collectd::_fc_register (type, name)
 *
 * type:
 *   match | target
 *
 * name:
 *   name of the match
 */
static XS(Collectd__fc_register) {
  int type;
  char *name;

  int ret = 0;

  dXSARGS;

  if (2 != items) {
    log_err("Usage: Collectd::_fc_register(type, name)");
    XSRETURN_EMPTY;
  }

  type = SvIV(ST(0));
  name = SvPV_nolen(ST(1));

  if (FC_MATCH == type)
    ret = fc_register_match(name, pmatch);
  else if (FC_TARGET == type)
    ret = fc_register_target(name, ptarget);

  if (0 == ret)
    XSRETURN_YES;
  else
    XSRETURN_EMPTY;
} /* static XS (Collectd_fc_register) */

/*
 * Collectd::call_by_name (...).
 *
 * Call a Perl sub identified by its name passed through $Collectd::cb_name.
 */
static XS(Collectd_call_by_name) {
  SV *tmp = NULL;
  char *name = NULL;

  if (NULL == (tmp = get_sv("Collectd::cb_name", 0))) {
    sv_setpv(get_sv("@", 1), "cb_name has not been set");
    CLEAR_STACK_FRAME;
    return;
  }

  name = SvPV_nolen(tmp);

  if (NULL == get_cv(name, 0)) {
    sv_setpvf(get_sv("@", 1), "unknown callback \"%s\"", name);
    CLEAR_STACK_FRAME;
    return;
  }

  /* simply pass on the subroutine call without touching the stack,
   * thus leaving any arguments and return values in place */
  call_pv(name, 0);
} /* static XS (Collectd_call_by_name) */

/*
 * Interface to collectd.
 */

static int perl_init(void) {
  int status;
  dTHX;

  if (NULL == perl_threads)
    return 0;

  if (NULL == aTHX) {
    c_ithread_t *t = NULL;

    pthread_mutex_lock(&perl_threads->mutex);
    t = c_ithread_create(perl_threads->head->interp);
    pthread_mutex_unlock(&perl_threads->mutex);

    aTHX = t->interp;
  }

  log_debug("perl_init: c_ithread: interp = %p (active threads: %i)", aTHX,
            perl_threads->number_of_threads);

  /* Lock the base thread to avoid race conditions with c_ithread_create().
   * See https://github.com/collectd/collectd/issues/9 and
   *     https://github.com/collectd/collectd/issues/1706 for details.
  */
  assert(aTHX == perl_threads->head->interp);
  pthread_mutex_lock(&perl_threads->mutex);

  status = pplugin_call_all(aTHX_ PLUGIN_INIT);

  pthread_mutex_unlock(&perl_threads->mutex);

  return status;
} /* static int perl_init (void) */

static int perl_read(void) {
  dTHX;

  if (NULL == perl_threads)
    return 0;

  if (NULL == aTHX) {
    c_ithread_t *t = NULL;

    pthread_mutex_lock(&perl_threads->mutex);
    t = c_ithread_create(perl_threads->head->interp);
    pthread_mutex_unlock(&perl_threads->mutex);

    aTHX = t->interp;
  }

  /* Assert that we're not running as the base thread. Otherwise, we might
   * run into concurrency issues with c_ithread_create(). See
   * https://github.com/collectd/collectd/issues/9 for details. */
  assert(aTHX != perl_threads->head->interp);

  log_debug("perl_read: c_ithread: interp = %p (active threads: %i)", aTHX,
            perl_threads->number_of_threads);
  return pplugin_call_all(aTHX_ PLUGIN_READ);
} /* static int perl_read (void) */

static int perl_write(const data_set_t *ds, const value_list_t *vl,
                      user_data_t __attribute__((unused)) * user_data) {
  int status;
  dTHX;

  if (NULL == perl_threads)
    return 0;

  if (NULL == aTHX) {
    c_ithread_t *t = NULL;

    pthread_mutex_lock(&perl_threads->mutex);
    t = c_ithread_create(perl_threads->head->interp);
    pthread_mutex_unlock(&perl_threads->mutex);

    aTHX = t->interp;
  }

  /* Lock the base thread if this is not called from one of the read threads
   * to avoid race conditions with c_ithread_create(). See
   * https://github.com/collectd/collectd/issues/9 for details. */
  if (aTHX == perl_threads->head->interp)
    pthread_mutex_lock(&perl_threads->mutex);

  log_debug("perl_write: c_ithread: interp = %p (active threads: %i)", aTHX,
            perl_threads->number_of_threads);
  status = pplugin_call_all(aTHX_ PLUGIN_WRITE, ds, vl);

  if (aTHX == perl_threads->head->interp)
    pthread_mutex_unlock(&perl_threads->mutex);

  return status;
} /* static int perl_write (const data_set_t *, const value_list_t *) */

static void perl_log(int level, const char *msg,
                     user_data_t __attribute__((unused)) * user_data) {
  dTHX;

  if (NULL == perl_threads)
    return;

  if (NULL == aTHX) {
    c_ithread_t *t = NULL;

    pthread_mutex_lock(&perl_threads->mutex);
    t = c_ithread_create(perl_threads->head->interp);
    pthread_mutex_unlock(&perl_threads->mutex);

    aTHX = t->interp;
  }

  /* Lock the base thread if this is not called from one of the read threads
   * to avoid race conditions with c_ithread_create(). See
   * https://github.com/collectd/collectd/issues/9 for details.
  */

  if (aTHX == perl_threads->head->interp)
    pthread_mutex_lock(&perl_threads->mutex);

  pplugin_call_all(aTHX_ PLUGIN_LOG, level, msg);

  if (aTHX == perl_threads->head->interp)
    pthread_mutex_unlock(&perl_threads->mutex);

  return;
} /* static void perl_log (int, const char *) */

static int perl_notify(const notification_t *notif,
                       user_data_t __attribute__((unused)) * user_data) {
  dTHX;

  if (NULL == perl_threads)
    return 0;

  if (NULL == aTHX) {
    c_ithread_t *t = NULL;

    pthread_mutex_lock(&perl_threads->mutex);
    t = c_ithread_create(perl_threads->head->interp);
    pthread_mutex_unlock(&perl_threads->mutex);

    aTHX = t->interp;
  }
  return pplugin_call_all(aTHX_ PLUGIN_NOTIF, notif);
} /* static int perl_notify (const notification_t *) */

static int perl_flush(cdtime_t timeout, const char *identifier,
                      user_data_t __attribute__((unused)) * user_data) {
  dTHX;

  if (NULL == perl_threads)
    return 0;

  if (NULL == aTHX) {
    c_ithread_t *t = NULL;

    pthread_mutex_lock(&perl_threads->mutex);
    t = c_ithread_create(perl_threads->head->interp);
    pthread_mutex_unlock(&perl_threads->mutex);

    aTHX = t->interp;
  }
  return pplugin_call_all(aTHX_ PLUGIN_FLUSH, timeout, identifier);
} /* static int perl_flush (const int) */

static int perl_shutdown(void) {
  c_ithread_t *t;
  int ret;

  dTHX;

  plugin_unregister_complex_config("perl");

  if (NULL == perl_threads)
    return 0;

  if (NULL == aTHX) {
    pthread_mutex_lock(&perl_threads->mutex);
    t = c_ithread_create(perl_threads->head->interp);
    pthread_mutex_unlock(&perl_threads->mutex);

    aTHX = t->interp;
  }

  log_debug("perl_shutdown: c_ithread: interp = %p (active threads: %i)", aTHX,
            perl_threads->number_of_threads);

  plugin_unregister_log("perl");
  plugin_unregister_notification("perl");
  plugin_unregister_init("perl");
  plugin_unregister_read("perl");
  plugin_unregister_write("perl");
  plugin_unregister_flush("perl");

  ret = pplugin_call_all(aTHX_ PLUGIN_SHUTDOWN);

  pthread_mutex_lock(&perl_threads->mutex);
  t = perl_threads->tail;

  while (NULL != t) {
    struct timespec ts_wait;
    c_ithread_t *thr = t;

    /* the pointer has to be advanced before destroying
     * the thread as this will free the memory */
    t = t->prev;

    thr->shutdown = 1;
    if (thr->running) {
      /* Give some time to thread to exit from Perl interpreter */
      WARNING("perl shutdown: Thread is running inside Perl. Waiting.");
      ts_wait.tv_sec = 0;
      ts_wait.tv_nsec = 500000;
      nanosleep(&ts_wait, NULL);
    }
    if (thr->running) {
      pthread_kill(thr->pthread, SIGTERM);
      ERROR("perl shutdown: Thread hangs inside Perl. Thread killed.");
    }
    c_ithread_destroy(thr);
  }

  pthread_mutex_unlock(&perl_threads->mutex);
  pthread_mutex_destroy(&perl_threads->mutex);
  pthread_mutexattr_destroy(&perl_threads->mutexattr);

  sfree(perl_threads);

  pthread_key_delete(perl_thr_key);

  PERL_SYS_TERM();

  plugin_unregister_shutdown("perl");
  return ret;
} /* static void perl_shutdown (void) */

/*
 * Access functions for global variables.
 *
 * These functions implement the "magic" used to access
 * the global variables from Perl.
 */

static int g_pv_get(pTHX_ SV *var, MAGIC *mg) {
  char *pv = mg->mg_ptr;
  sv_setpv(var, pv);
  return 0;
} /* static int g_pv_get (pTHX_ SV *, MAGIC *) */

static int g_pv_set(pTHX_ SV *var, MAGIC *mg) {
  char *pv = mg->mg_ptr;
  sstrncpy(pv, SvPV_nolen(var), DATA_MAX_NAME_LEN);
  return 0;
} /* static int g_pv_set (pTHX_ SV *, MAGIC *) */

static int g_interval_get(pTHX_ SV *var, MAGIC *mg) {
  log_warn("Accessing $interval_g is deprecated (and might not "
           "give the desired results) - plugin_get_interval() should "
           "be used instead.");
  sv_setnv(var, CDTIME_T_TO_DOUBLE(interval_g));
  return 0;
} /* static int g_interval_get (pTHX_ SV *, MAGIC *) */

static int g_interval_set(pTHX_ SV *var, MAGIC *mg) {
  double nv = (double)SvNV(var);
  log_warn("Accessing $interval_g is deprecated (and might not "
           "give the desired results) - plugin_get_interval() should "
           "be used instead.");
  interval_g = DOUBLE_TO_CDTIME_T(nv);
  return 0;
} /* static int g_interval_set (pTHX_ SV *, MAGIC *) */

static MGVTBL g_pv_vtbl = {g_pv_get, g_pv_set, NULL, NULL, NULL, NULL, NULL
#if HAVE_PERL_STRUCT_MGVTBL_SVT_LOCAL
                           ,
                           NULL
#endif
};
static MGVTBL g_interval_vtbl = {g_interval_get, g_interval_set, NULL, NULL,
                                 NULL, NULL, NULL
#if HAVE_PERL_STRUCT_MGVTBL_SVT_LOCAL
                                 ,
                                 NULL
#endif
};

/* bootstrap the Collectd module */
static void xs_init(pTHX) {
  HV *stash = NULL;
  SV *tmp = NULL;
  char *file = __FILE__;

  dXSUB_SYS;

  /* enable usage of Perl modules using shared libraries */
  newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);

  /* register API */
  for (int i = 0; NULL != api[i].f; ++i)
    newXS(api[i].name, api[i].f, file);

  stash = gv_stashpv("Collectd", 1);

  /* export "constants" */
  for (int i = 0; '\0' != constants[i].name[0]; ++i)
    newCONSTSUB(stash, constants[i].name, newSViv(constants[i].value));

  /* export global variables
   * by adding "magic" to the SV's representing the globale variables
   * perl is able to automagically call the get/set function when
   * accessing any such variable (this is basically the same as using
   * tie() in Perl) */
  /* global strings */
  for (int i = 0; '\0' != g_strings[i].name[0]; ++i) {
    tmp = get_sv(g_strings[i].name, 1);
    sv_magicext(tmp, NULL, PERL_MAGIC_ext, &g_pv_vtbl, g_strings[i].var, 0);
  }

  tmp = get_sv("Collectd::interval_g", /* create = */ 1);
  sv_magicext(tmp, NULL, /* how = */ PERL_MAGIC_ext,
              /* vtbl = */ &g_interval_vtbl,
              /* name = */ NULL, /* namelen = */ 0);

  return;
} /* static void xs_init (pTHX) */

/* Initialize the global Perl interpreter. */
static int init_pi(int argc, char **argv) {
  dTHXa(NULL);

  if (NULL != perl_threads)
    return 0;

  log_info("Initializing Perl interpreter...");
#if COLLECT_DEBUG
  {
    for (int i = 0; i < argc; ++i)
      log_debug("argv[%i] = \"%s\"", i, argv[i]);
  }
#endif /* COLLECT_DEBUG */

  if (0 != pthread_key_create(&perl_thr_key, c_ithread_destructor)) {
    log_err("init_pi: pthread_key_create failed");

    /* this must not happen - cowardly giving up if it does */
    return -1;
  }

#ifdef __FreeBSD__
  /* On FreeBSD, PERL_SYS_INIT3 expands to some expression which
   * triggers a "value computed is not used" warning by gcc. */
  (void)
#endif
      PERL_SYS_INIT3(&argc, &argv, &environ);

  perl_threads = smalloc(sizeof(*perl_threads));
  memset(perl_threads, 0, sizeof(c_ithread_list_t));

  pthread_mutexattr_init(&perl_threads->mutexattr);
  pthread_mutexattr_settype(&perl_threads->mutexattr, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&perl_threads->mutex, &perl_threads->mutexattr);
  /* locking the mutex should not be necessary at this point
   * but let's just do it for the sake of completeness */
  pthread_mutex_lock(&perl_threads->mutex);

  perl_threads->head = c_ithread_create(NULL);
  perl_threads->tail = perl_threads->head;

  if (NULL == (perl_threads->head->interp = perl_alloc())) {
    log_err("init_pi: Not enough memory.");
    exit(3);
  }

  aTHX = perl_threads->head->interp;
  pthread_mutex_unlock(&perl_threads->mutex);

  perl_construct(aTHX);

  PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

  if (0 != perl_parse(aTHX_ xs_init, argc, argv, NULL)) {
    SV *err = get_sv("@", 1);
    log_err("init_pi: Unable to bootstrap Collectd: %s", SvPV_nolen(err));

    perl_destruct(perl_threads->head->interp);
    perl_free(perl_threads->head->interp);
    sfree(perl_threads);

    pthread_key_delete(perl_thr_key);
    return -1;
  }

  /* Set $0 to "collectd" because perl_parse() has to set it to "-e". */
  sv_setpv(get_sv("0", 0), "collectd");

  perl_run(aTHX);

  plugin_register_log("perl", perl_log, /* user_data = */ NULL);
  plugin_register_notification("perl", perl_notify,
                               /* user_data = */ NULL);
  plugin_register_init("perl", perl_init);

  plugin_register_read("perl", perl_read);

  plugin_register_write("perl", perl_write, /* user_data = */ NULL);
  plugin_register_flush("perl", perl_flush, /* user_data = */ NULL);
  plugin_register_shutdown("perl", perl_shutdown);
  return 0;
} /* static int init_pi (const char **, const int) */

/*
 * LoadPlugin "<Plugin>"
 */
static int perl_config_loadplugin(pTHX_ oconfig_item_t *ci) {
  char module_name[DATA_MAX_NAME_LEN];

  char *value = NULL;

  if ((0 != ci->children_num) || (1 != ci->values_num) ||
      (OCONFIG_TYPE_STRING != ci->values[0].type)) {
    log_err("LoadPlugin expects a single string argument.");
    return 1;
  }

  value = ci->values[0].value.string;

  if (NULL == get_module_name(module_name, sizeof(module_name), value)) {
    log_err("Invalid module name %s", value);
    return (1);
  }

  if (0 != init_pi(perl_argc, perl_argv))
    return -1;

  assert(NULL != perl_threads);
  assert(NULL != perl_threads->head);

  aTHX = perl_threads->head->interp;

  log_debug("perl_config: Loading Perl plugin \"%s\"", value);
  load_module(PERL_LOADMOD_NOIMPORT, newSVpv(module_name, strlen(module_name)),
              Nullsv);
  return 0;
} /* static int perl_config_loadplugin (oconfig_item_it *) */

/*
 * BaseName "<Name>"
 */
static int perl_config_basename(pTHX_ oconfig_item_t *ci) {
  char *value = NULL;

  if ((0 != ci->children_num) || (1 != ci->values_num) ||
      (OCONFIG_TYPE_STRING != ci->values[0].type)) {
    log_err("BaseName expects a single string argument.");
    return 1;
  }

  value = ci->values[0].value.string;

  log_debug("perl_config: Setting plugin basename to \"%s\"", value);
  sstrncpy(base_name, value, sizeof(base_name));
  return 0;
} /* static int perl_config_basename (oconfig_item_it *) */

/*
 * EnableDebugger "<Package>"|""
 */
static int perl_config_enabledebugger(pTHX_ oconfig_item_t *ci) {
  char *value = NULL;

  if ((0 != ci->children_num) || (1 != ci->values_num) ||
      (OCONFIG_TYPE_STRING != ci->values[0].type)) {
    log_err("EnableDebugger expects a single string argument.");
    return 1;
  }

  if (NULL != perl_threads) {
    log_warn("EnableDebugger has no effects if used after LoadPlugin.");
    return 1;
  }

  value = ci->values[0].value.string;

  perl_argv = realloc(perl_argv, (++perl_argc + 1) * sizeof(char *));

  if (NULL == perl_argv) {
    log_err("perl_config: Not enough memory.");
    exit(3);
  }

  if ('\0' == value[0]) {
    perl_argv[perl_argc - 1] = "-d";
  } else {
    perl_argv[perl_argc - 1] = smalloc(strlen(value) + 4);
    sstrncpy(perl_argv[perl_argc - 1], "-d:", 4);
    sstrncpy(perl_argv[perl_argc - 1] + 3, value, strlen(value) + 1);
  }

  perl_argv[perl_argc] = NULL;
  return 0;
} /* static int perl_config_enabledebugger (oconfig_item_it *) */

/*
 * IncludeDir "<Dir>"
 */
static int perl_config_includedir(pTHX_ oconfig_item_t *ci) {
  char *value = NULL;

  if ((0 != ci->children_num) || (1 != ci->values_num) ||
      (OCONFIG_TYPE_STRING != ci->values[0].type)) {
    log_err("IncludeDir expects a single string argument.");
    return 1;
  }

  value = ci->values[0].value.string;

  if (NULL == aTHX) {
    perl_argv = realloc(perl_argv, (++perl_argc + 1) * sizeof(char *));

    if (NULL == perl_argv) {
      log_err("perl_config: Not enough memory.");
      exit(3);
    }

    perl_argv[perl_argc - 1] = smalloc(strlen(value) + 3);
    sstrncpy(perl_argv[perl_argc - 1], "-I", 3);
    sstrncpy(perl_argv[perl_argc - 1] + 2, value, strlen(value) + 1);

    perl_argv[perl_argc] = NULL;
  } else {
    /* prepend the directory to @INC */
    av_unshift(GvAVn(PL_incgv), 1);
    av_store(GvAVn(PL_incgv), 0, newSVpv(value, strlen(value)));
  }
  return 0;
} /* static int perl_config_includedir (oconfig_item_it *) */

/*
 * <Plugin> block
 */
static int perl_config_plugin(pTHX_ oconfig_item_t *ci) {
  int retvals = 0;
  int ret = 0;

  char *plugin;
  HV *config;

  dSP;

  if ((1 != ci->values_num) || (OCONFIG_TYPE_STRING != ci->values[0].type)) {
    log_err("LoadPlugin expects a single string argument.");
    return 1;
  }

  plugin = ci->values[0].value.string;
  config = newHV();

  if (0 != oconfig_item2hv(aTHX_ ci, config)) {
    hv_clear(config);
    hv_undef(config);

    log_err("Unable to convert configuration to a Perl hash value.");
    config = (HV *)&PL_sv_undef;
  }

  ENTER;
  SAVETMPS;

  PUSHMARK(SP);

  XPUSHs(sv_2mortal(newSVpv(plugin, 0)));
  XPUSHs(sv_2mortal(newRV_noinc((SV *)config)));

  PUTBACK;

  retvals = call_pv("Collectd::_plugin_dispatch_config", G_SCALAR);

  SPAGAIN;
  if (0 < retvals) {
    SV *tmp = POPs;
    if (!SvTRUE(tmp))
      ret = 1;
  } else
    ret = 1;

  PUTBACK;
  FREETMPS;
  LEAVE;
  return ret;
} /* static int perl_config_plugin (oconfig_item_it *) */

static int perl_config(oconfig_item_t *ci) {
  int status = 0;

  dTHXa(NULL);

  for (int i = 0; i < ci->children_num; ++i) {
    oconfig_item_t *c = ci->children + i;
    int current_status = 0;

    if (NULL != perl_threads) {
      if ((aTHX = PERL_GET_CONTEXT) == NULL)
        return -1;
    }

    if (0 == strcasecmp(c->key, "LoadPlugin"))
      current_status = perl_config_loadplugin(aTHX_ c);
    else if (0 == strcasecmp(c->key, "BaseName"))
      current_status = perl_config_basename(aTHX_ c);
    else if (0 == strcasecmp(c->key, "EnableDebugger"))
      current_status = perl_config_enabledebugger(aTHX_ c);
    else if (0 == strcasecmp(c->key, "IncludeDir"))
      current_status = perl_config_includedir(aTHX_ c);
    else if (0 == strcasecmp(c->key, "Plugin"))
      current_status = perl_config_plugin(aTHX_ c);
    else {
      log_warn("Ignoring unknown config key \"%s\".", c->key);
      current_status = 0;
    }

    /* fatal error - it's up to perl_config_* to clean up */
    if (0 > current_status) {
      log_err("Configuration failed with a fatal error - "
              "plugin disabled!");
      return current_status;
    }

    status += current_status;
  }
  return status;
} /* static int perl_config (oconfig_item_t *) */

void module_register(void) {
  perl_argc = 4;
  perl_argv = smalloc((perl_argc + 1) * sizeof(*perl_argv));

  /* default options for the Perl interpreter */
  perl_argv[0] = "";
  perl_argv[1] = "-MCollectd";
  perl_argv[2] = "-e";
  perl_argv[3] = "1";
  perl_argv[4] = NULL;

  plugin_register_complex_config("perl", perl_config);
  return;
} /* void module_register (void) */

/* vim: set sw=4 ts=4 tw=78 noexpandtab : */
