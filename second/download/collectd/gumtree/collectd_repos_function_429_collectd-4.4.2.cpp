static int pplugin_call_all (pTHX_ int type, ...)
{
	int retvals = 0;

	va_list ap;
	int ret = 0;

	dSP;

	if ((type < 0) || (type >= PLUGIN_TYPES))
		return -1;

	va_start (ap, type);

	ENTER;
	SAVETMPS;

	PUSHMARK (SP);

	XPUSHs (sv_2mortal (newSViv ((IV)type)));

	if (PLUGIN_WRITE == type) {
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
		 *   plugin_instance => $instance,
		 *   type_instance   => $type_instance
		 * };
		 */
		data_set_t   *ds;
		value_list_t *vl;

		AV *pds = newAV ();
		HV *pvl = newHV ();

		ds = va_arg (ap, data_set_t *);
		vl = va_arg (ap, value_list_t *);

		if (-1 == data_set2av (aTHX_ ds, pds)) {
			av_clear (pds);
			av_undef (pds);
			pds = Nullav;
			ret = -1;
		}

		if (-1 == value_list2hv (aTHX_ vl, ds, pvl)) {
			hv_clear (pvl);
			hv_undef (pvl);
			pvl = Nullhv;
			ret = -1;
		}

		XPUSHs (sv_2mortal (newSVpv (ds->type, 0)));
		XPUSHs (sv_2mortal (newRV_noinc ((SV *)pds)));
		XPUSHs (sv_2mortal (newRV_noinc ((SV *)pvl)));
	}
	else if (PLUGIN_LOG == type) {
		/*
		 * $_[0] = $level;
		 *
		 * $_[1] = $message;
		 */
		XPUSHs (sv_2mortal (newSViv (va_arg (ap, int))));
		XPUSHs (sv_2mortal (newSVpv (va_arg (ap, char *), 0)));
	}
	else if (PLUGIN_NOTIF == type) {
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
		notification_t *n;
		HV *notif = newHV ();

		n = va_arg (ap, notification_t *);

		if (-1 == notification2hv (aTHX_ n, notif)) {
			hv_clear (notif);
			hv_undef (notif);
			notif = Nullhv;
			ret = -1;
		}

		XPUSHs (sv_2mortal (newRV_noinc ((SV *)notif)));
	}
	else if (PLUGIN_FLUSH == type) {
		/*
		 * $_[0] = $timeout;
		 */
		XPUSHs (sv_2mortal (newSViv (va_arg (ap, int))));
	}

	PUTBACK;

	retvals = call_pv ("Collectd::plugin_call_all", G_SCALAR);

	SPAGAIN;
	if (0 < retvals) {
		SV *tmp = POPs;
		if (! SvTRUE (tmp))
			ret = -1;
	}

	PUTBACK;
	FREETMPS;
	LEAVE;

	va_end (ap);
	return ret;
}