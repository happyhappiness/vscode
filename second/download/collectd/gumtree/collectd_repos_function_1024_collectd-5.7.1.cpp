static int pplugin_call(pTHX_ int type, ...) {
  int retvals = 0;

  va_list ap;
  int ret = 0;
  char *subname;

  dSP;

  if ((type < 0) || (type >= PLUGIN_TYPES))
    return -1;

  va_start(ap, type);

  ENTER;
  SAVETMPS;

  PUSHMARK(SP);

  if (PLUGIN_READ == type) {
    subname = va_arg(ap, char *);
  } else if (PLUGIN_WRITE == type) {
    data_set_t *ds;
    value_list_t *vl;

    AV *pds = newAV();
    HV *pvl = newHV();

    subname = va_arg(ap, char *);
    /*
     * $_[0] = $plugin_type;
     *
     * $_[1] =
     * [
     *   {
     *     name => $ds_name,
     *     type => $ds_type,
     *     min  => $ds_min,
     *     max  => $ds_max
     *   },
     *   ...
     * ];
     *
     * $_[2] =
     * {
     *   values => [ $v1, ... ],
     *   time   => $time,
     *   host   => $hostname,
     *   plugin => $plugin,
     *   type   => $type,
     *   plugin_instance => $instance,
     *   type_instance   => $type_instance
     * };
     */
    ds = va_arg(ap, data_set_t *);
    vl = va_arg(ap, value_list_t *);

    if (-1 == data_set2av(aTHX_ ds, pds)) {
      av_clear(pds);
      av_undef(pds);
      pds = (AV *)&PL_sv_undef;
      ret = -1;
    }

    if (-1 == value_list2hv(aTHX_ vl, ds, pvl)) {
      hv_clear(pvl);
      hv_undef(pvl);
      pvl = (HV *)&PL_sv_undef;
      ret = -1;
    }

    XPUSHs(sv_2mortal(newSVpv(ds->type, 0)));
    XPUSHs(sv_2mortal(newRV_noinc((SV *)pds)));
    XPUSHs(sv_2mortal(newRV_noinc((SV *)pvl)));
  } else if (PLUGIN_LOG == type) {
    subname = va_arg(ap, char *);
    /*
     * $_[0] = $level;
     *
     * $_[1] = $message;
     */
    XPUSHs(sv_2mortal(newSViv(va_arg(ap, int))));
    XPUSHs(sv_2mortal(newSVpv(va_arg(ap, char *), 0)));
  } else if (PLUGIN_NOTIF == type) {
    notification_t *n;
    HV *notif = newHV();

    subname = va_arg(ap, char *);
    /*
     * $_[0] =
     * {
     *   severity => $severity,
     *   time     => $time,
     *   message  => $msg,
     *   host     => $host,
     *   plugin   => $plugin,
     *   type     => $type,
     *   plugin_instance => $instance,
     *   type_instance   => $type_instance
     * };
     */
    n = va_arg(ap, notification_t *);

    if (-1 == notification2hv(aTHX_ n, notif)) {
      hv_clear(notif);
      hv_undef(notif);
      notif = (HV *)&PL_sv_undef;
      ret = -1;
    }

    XPUSHs(sv_2mortal(newRV_noinc((SV *)notif)));
  } else if (PLUGIN_FLUSH == type) {
    cdtime_t timeout;
    subname = va_arg(ap, char *);
    /*
     * $_[0] = $timeout;
     * $_[1] = $identifier;
     */
    timeout = va_arg(ap, cdtime_t);

    XPUSHs(sv_2mortal(newSVnv(CDTIME_T_TO_DOUBLE(timeout))));
    XPUSHs(sv_2mortal(newSVpv(va_arg(ap, char *), 0)));
  } else if (PLUGIN_FLUSH_ALL == type) {
    cdtime_t timeout;
    subname = "Collectd::plugin_call_all";
    /*
     * $_[0] = $timeout;
     * $_[1] = $identifier;
     */
    timeout = va_arg(ap, cdtime_t);

    XPUSHs(sv_2mortal(newSViv((IV)PLUGIN_FLUSH)));
    XPUSHs(sv_2mortal(newSVnv(CDTIME_T_TO_DOUBLE(timeout))));
    XPUSHs(sv_2mortal(newSVpv(va_arg(ap, char *), 0)));
  } else if (PLUGIN_INIT == type) {
    subname = "Collectd::plugin_call_all";
    XPUSHs(sv_2mortal(newSViv((IV)type)));
  } else if (PLUGIN_SHUTDOWN == type) {
    subname = "Collectd::plugin_call_all";
    XPUSHs(sv_2mortal(newSViv((IV)type)));
  } else { /* Unknown type. Run 'plugin_call_all' and make compiler happy */
    subname = "Collectd::plugin_call_all";
    XPUSHs(sv_2mortal(newSViv((IV)type)));
  }

  PUTBACK;

  retvals = call_pv_locked(aTHX_ subname);

  SPAGAIN;
  if (SvTRUE(ERRSV)) {
    if (PLUGIN_LOG != type)
      ERROR("perl: %s error: %s", subname, SvPV_nolen(ERRSV));
    ret = -1;
  } else if (0 < retvals) {
    SV *tmp = POPs;
    if (!SvTRUE(tmp))
      ret = -1;
  }

  PUTBACK;
  FREETMPS;
  LEAVE;

  va_end(ap);
  return ret;
}