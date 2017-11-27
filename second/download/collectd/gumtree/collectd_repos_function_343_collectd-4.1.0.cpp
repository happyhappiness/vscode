static int pplugin_call (int type, char *name, SV *sub, va_list ap)
{
	int retvals = 0;
	I32 xflags  = G_NOARGS;

	int ret = 0;

	dSP;

	if ((type < 0) || (type >= PLUGIN_TYPES))
		return -1;

	ENTER;
	SAVETMPS;

	PUSHMARK (SP);

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

		xflags = 0;
	}
	else if (PLUGIN_LOG == type) {
		/*
		 * $_[0] = $level;
		 *
		 * $_[1] = $message;
		 */
		XPUSHs (sv_2mortal (Perl_newSViv (perl, va_arg (ap, int))));
		XPUSHs (sv_2mortal (Perl_newSVpv (perl, va_arg (ap, char *), 0)));

		xflags = 0;
	}

	PUTBACK;

	/* prevent an endless loop */
	if (PLUGIN_LOG != type)
		log_debug ("pplugin_call: executing %s::%s->%s()",
				base_name, name, plugin_types[type]);

	retvals = Perl_call_sv (perl, sub, G_SCALAR | xflags);

	SPAGAIN;
	if (1 > retvals) {
		if (PLUGIN_LOG != type)
			log_warn ("pplugin_call: "
					"%s::%s->%s() returned void - assuming true",
					base_name, name, plugin_types[type]);
	}
	else {
		SV *tmp = POPs;
		if (! SvTRUE (tmp))
			ret = -1;
	}

	PUTBACK;
	FREETMPS;
	LEAVE;
	return ret;
}