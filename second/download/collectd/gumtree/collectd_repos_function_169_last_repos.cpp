static int varnish_read(user_data_t *ud) /* {{{ */
{
#if HAVE_VARNISH_V3 || HAVE_VARNISH_V4
  struct VSM_data *vd;
  _Bool ok;
  const c_varnish_stats_t *stats;
#elif HAVE_VARNISH_V5
  struct vsm *vd;
  struct vsc *vsc;
  int vsm_status;
#endif

  user_config_t *conf;

  if ((ud == NULL) || (ud->data == NULL))
    return EINVAL;

  conf = ud->data;

  vd = VSM_New();

#if HAVE_VARNISH_V5
  vsc = VSC_New();
#endif

#if HAVE_VARNISH_V3
  VSC_Setup(vd);
#endif

  if (conf->instance != NULL) {
    int status;

#if HAVE_VARNISH_V3 || HAVE_VARNISH_V4
    status = VSM_n_Arg(vd, conf->instance);
#elif HAVE_VARNISH_V5
    status = VSM_Arg(vd, 'n', conf->instance);
#endif

    if (status < 0) {
#if HAVE_VARNISH_V3 || HAVE_VARNISH_V4
      VSM_Delete(vd);
#elif HAVE_VARNISH_V5
      VSC_Destroy(&vsc, vd);
      VSM_Destroy(&vd);
#endif
      ERROR("varnish plugin: VSM_Arg (\"%s\") failed "
            "with status %i.",
            conf->instance, status);
      return -1;
    }
  }

#if HAVE_VARNISH_V3
  ok = (VSC_Open(vd, /* diag = */ 1) == 0);
#elif HAVE_VARNISH_V4
  ok = (VSM_Open(vd) == 0);
#endif
#if HAVE_VARNISH_V3 || HAVE_VARNISH_V4
  if (!ok) {
    VSM_Delete(vd);
    ERROR("varnish plugin: Unable to open connection.");
    return -1;
  }
#endif

#if HAVE_VARNISH_V3
  stats = VSC_Main(vd);
#elif HAVE_VARNISH_V4
  stats = VSC_Main(vd, NULL);
#endif
#if HAVE_VARNISH_V3 || HAVE_VARNISH_V4
  if (!stats) {
    VSM_Delete(vd);
    ERROR("varnish plugin: Unable to get statistics.");
    return -1;
  }
#endif

#if HAVE_VARNISH_V5
  if (VSM_Attach(vd, STDERR_FILENO)) {
    ERROR("varnish plugin: Cannot attach to varnish. %s", VSM_Error(vd));
    VSC_Destroy(&vsc, vd);
    VSM_Destroy(&vd);
    return -1;
  }

  vsm_status = VSM_Status(vd);
  if (vsm_status & ~(VSM_MGT_RUNNING | VSM_WRK_RUNNING)) {
    ERROR("varnish plugin: Unable to get statistics.");
    VSC_Destroy(&vsc, vd);
    VSM_Destroy(&vd);
    return -1;
  }
#endif

#if HAVE_VARNISH_V3
  VSC_Iter(vd, varnish_monitor, conf);
#elif HAVE_VARNISH_V4
  VSC_Iter(vd, NULL, varnish_monitor, conf);
#elif HAVE_VARNISH_V5
  VSC_Iter(vsc, vd, varnish_monitor, conf);
#endif

#if HAVE_VARNISH_V3 || HAVE_VARNISH_V4
  VSM_Delete(vd);
#elif HAVE_VARNISH_V5
  VSC_Destroy(&vsc, vd);
  VSM_Destroy(&vd);
#endif

  return 0;
}