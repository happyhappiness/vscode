static int pplugin_call_all (int type, ...)
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

	XPUSHs (sv_2mortal (Perl_newSViv (perl, (IV)type)));

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

		AV *pds = Perl_newAV (perl);
		HV *pvl = Perl_newHV (perl);

		ds = va_arg (ap, data_set_t *);
		vl = va_arg (ap, value_list_t *);

		if (-1 == data_set2av (ds, pds))
			return -1;

		if (-1 == value_list2hv (vl, ds, pvl))
			return -1;

		XPUSHs (sv_2mortal (Perl_newSVpv (perl, ds->type, 0)));
		XPUSHs (sv_2mortal (Perl_newRV_noinc (perl, (SV *)pds)));
		XPUSHs (sv_2mortal (Perl_newRV_noinc (perl, (SV *)pvl)));
	}
	else if (PLUGIN_LOG == type) {
		/*
		 * $_[0] = $level;
		 *
		 * $_[1] = $message;
		 */
		XPUSHs (sv_2mortal (Perl_newSViv (perl, va_arg (ap, int))));
		XPUSHs (sv_2mortal (Perl_newSVpv (perl, va_arg (ap, char *), 0)));
	}

	PUTBACK;

	retvals = Perl_call_pv (perl, "Collectd::plugin_call_all", G_SCALAR);

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