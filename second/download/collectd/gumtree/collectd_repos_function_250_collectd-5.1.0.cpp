static int varnish_config_apply_default (user_config_t *conf) /* {{{ */
{
	if (conf == NULL)
		return (EINVAL);

	conf->collect_backend     = 1;
	conf->collect_cache       = 1;
	conf->collect_connections = 1;
	conf->collect_esi         = 0;
	conf->collect_fetch       = 0;
	conf->collect_hcb         = 0;
	conf->collect_shm         = 1;
#if HAVE_VARNISH_V2
	conf->collect_sm          = 0;
	conf->collect_sma         = 0;
#endif
	conf->collect_sms         = 0;
	conf->collect_totals      = 0;

	return (0);
}