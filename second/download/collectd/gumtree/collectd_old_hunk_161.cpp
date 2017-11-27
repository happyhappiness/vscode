		XSRETURN_EMPTY;
	}

	if ((NULL == ST (0)) || (NULL == values))
		XSRETURN_EMPTY;

	ret = pplugin_dispatch_values (SvPV_nolen (ST (0)), (HV *)SvRV (values));

	if (0 == ret)
		XSRETURN_YES;
	else
		XSRETURN_EMPTY;
} /* static XS (Collectd_plugin_dispatch_values) */

/*
 * Collectd::plugin_log (level, message).
 *
 * level:
 *   log level (LOG_DEBUG, ... LOG_ERR)
 *
 * message:
