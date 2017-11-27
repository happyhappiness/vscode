static int perl_config_plugin (pTHX_ oconfig_item_t *ci)
{
	int retvals = 0;
	int ret     = 0;

	char *plugin;
	HV   *config;

	dSP;

	if ((1 != ci->values_num) || (OCONFIG_TYPE_STRING != ci->values[0].type)) {
		log_err ("LoadPlugin expects a single string argument.");
		return 1;
	}

	plugin = ci->values[0].value.string;
	config = newHV ();

	if (0 != oconfig_item2hv (aTHX_ ci, config)) {
		hv_clear (config);
		hv_undef (config);

		log_err ("Unable to convert configuration to a Perl hash value.");
		config = (HV *)&PL_sv_undef;
	}

	ENTER;
	SAVETMPS;

	PUSHMARK (SP);

	XPUSHs (sv_2mortal (newSVpv (plugin, 0)));
	XPUSHs (sv_2mortal (newRV_noinc ((SV *)config)));

	PUTBACK;

	retvals = call_pv ("Collectd::_plugin_dispatch_config", G_SCALAR);

	SPAGAIN;
	if (0 < retvals) {
		SV *tmp = POPs;
		if (! SvTRUE (tmp))
			ret = 1;
	}
	else
		ret = 1;

	PUTBACK;
	FREETMPS;
	LEAVE;
	return ret;
}