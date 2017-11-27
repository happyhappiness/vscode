		XSRETURN_EMPTY;
	}

	if ((NULL == ST (0)) || (NULL == values))
		XSRETURN_EMPTY;

	ret = pplugin_dispatch_values (aTHX_ SvPV_nolen (ST (0)),
			(HV *)SvRV (values));

	if (0 == ret)
		XSRETURN_YES;
	else
		XSRETURN_EMPTY;
} /* static XS (Collectd_plugin_dispatch_values) */

/*
 * Collectd::plugin_dispatch_notification (notif).
 *
 * notif:
 *   notification to dispatch
 */
static XS (Collectd_plugin_dispatch_notification)
{
	SV *notif = NULL;

	int ret = 0;

	dXSARGS;

	if (1 != items) {
		log_err ("Usage: Collectd::plugin_dispatch_notification(notif)");
		XSRETURN_EMPTY;
	}

	log_debug ("Collectd::plugin_dispatch_notification: notif = \"%s\"",
			SvPV_nolen (ST (0)));

	notif = ST (0);

	if (! (SvROK (notif) && (SVt_PVHV == SvTYPE (SvRV (notif))))) {
		log_err ("Collectd::plugin_dispatch_notification: Invalid notif.");
		XSRETURN_EMPTY;
	}

	ret = pplugin_dispatch_notification (aTHX_ (HV *)SvRV (notif));

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
