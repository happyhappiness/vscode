static int fc_call (pTHX_ int type, int cb_type, pfc_user_data_t *data, ...)
{
	int retvals = 0;

	va_list ap;
	int ret = 0;

	notification_meta_t **meta  = NULL;
	AV                   *pmeta = NULL;

	dSP;

	if ((type < 0) || (type >= FC_TYPES))
		return -1;

	if ((cb_type < 0) || (cb_type >= FC_CB_TYPES))
		return -1;

	va_start (ap, data);

	ENTER;
	SAVETMPS;

	PUSHMARK (SP);

	XPUSHs (sv_2mortal (newSViv ((IV)type)));
	XPUSHs (sv_2mortal (newSVpv (data->name, 0)));
	XPUSHs (sv_2mortal (newSViv ((IV)cb_type)));

	if (FC_CB_CREATE == cb_type) {
		/*
		 * $_[0] = $ci;
		 * $_[1] = $user_data;
		 */
		oconfig_item_t *ci;
		HV *config = newHV ();

		ci = va_arg (ap, oconfig_item_t *);

		if (0 != oconfig_item2hv (aTHX_ ci, config)) {
			hv_clear (config);
			hv_undef (config);
			config = (HV *)&PL_sv_undef;
			ret = -1;
		}

		XPUSHs (sv_2mortal (newRV_noinc ((SV *)config)));
	}
	else if (FC_CB_DESTROY == cb_type) {
		/*
		 * $_[1] = $user_data;
		 */

		/* nothing to be done - the user data pointer
		 * is pushed onto the stack later */
	}
	else if (FC_CB_EXEC == cb_type) {
		/*
		 * $_[0] = $ds;
		 * $_[1] = $vl;
		 * $_[2] = $meta;
		 * $_[3] = $user_data;
		 */
		data_set_t   *ds;
		value_list_t *vl;

		AV *pds = newAV ();
		HV *pvl = newHV ();

		ds   = va_arg (ap, data_set_t *);
		vl   = va_arg (ap, value_list_t *);
		meta = va_arg (ap, notification_meta_t **);

		if (0 != data_set2av (aTHX_ ds, pds)) {
			av_clear (pds);
			av_undef (pds);
			pds = (AV *)&PL_sv_undef;
			ret = -1;
		}

		if (0 != value_list2hv (aTHX_ vl, ds, pvl)) {
			hv_clear (pvl);
			hv_undef (pvl);
			pvl = (HV *)&PL_sv_undef;
			ret = -1;
		}

		if (NULL != meta) {
			pmeta = newAV ();

			if (0 != notification_meta2av (aTHX_ *meta, pmeta)) {
				av_clear (pmeta);
				av_undef (pmeta);
				pmeta = (AV *)&PL_sv_undef;
				ret = -1;
			}
		}
		else {
			pmeta = (AV *)&PL_sv_undef;
		}

		XPUSHs (sv_2mortal (newRV_noinc ((SV *)pds)));
		XPUSHs (sv_2mortal (newRV_noinc ((SV *)pvl)));
		XPUSHs (sv_2mortal (newRV_noinc ((SV *)pmeta)));
	}

	XPUSHs (sv_2mortal (newRV_inc (data->user_data)));

	PUTBACK;

	retvals = call_pv_locked (aTHX_ "Collectd::fc_call");

	if ((FC_CB_EXEC == cb_type) && (meta != NULL)) {
		assert (pmeta != NULL);

		plugin_notification_meta_free (*meta);
		av2notification_meta (aTHX_ pmeta, meta);
	}

	SPAGAIN;
	if (0 < retvals) {
		SV *tmp = POPs;

		/* the exec callbacks return a status, while
		 * the others return a boolean value */
		if (FC_CB_EXEC == cb_type)
			ret = SvIV (tmp);
		else if (! SvTRUE (tmp))
			ret = -1;
	}

	PUTBACK;
	FREETMPS;
	LEAVE;

	va_end (ap);
	return ret;
}