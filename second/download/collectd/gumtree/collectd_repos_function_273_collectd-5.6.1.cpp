static int varnish_config_apply_default (user_config_t *conf) /* {{{ */
{
	if (conf == NULL)
		return (EINVAL);

	conf->collect_backend     = 1;
	conf->collect_cache       = 1;
	conf->collect_connections = 1;
#ifdef HAVE_VARNISH_V3
	conf->collect_dirdns      = 0;
#endif
	conf->collect_esi         = 0;
	conf->collect_fetch       = 0;
	conf->collect_hcb         = 0;
	conf->collect_objects     = 0;
#if HAVE_VARNISH_V2
	conf->collect_purge       = 0;
#else
	conf->collect_ban         = 0;
#endif
	conf->collect_session     = 0;
	conf->collect_shm         = 1;
#if HAVE_VARNISH_V2
	conf->collect_sm          = 0;
	conf->collect_sma         = 0;
#endif
	conf->collect_sms         = 0;
	conf->collect_struct      = 0;
	conf->collect_totals      = 0;
#if HAVE_VARNISH_V3 || HAVE_VARNISH_V4
	conf->collect_uptime      = 0;
#endif
	conf->collect_vcl         = 0;
	conf->collect_workers     = 0;
#if HAVE_VARNISH_V4
	conf->collect_vsm         = 0;
#endif

	return (0);
}