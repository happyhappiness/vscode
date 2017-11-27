static int varnish_read (user_data_t *ud) /* {{{ */
{
	struct VSM_data *vd;
	const c_varnish_stats_t *stats;

	user_config_t *conf;

	if ((ud == NULL) || (ud->data == NULL))
		return (EINVAL);

	conf = ud->data;

	vd = VSM_New();
#if HAVE_VARNISH_V3
	VSC_Setup(vd);
#endif

	if (conf->instance != NULL)
	{
		int status;

		status = VSM_n_Arg (vd, conf->instance);
		if (status < 0)
		{
			VSM_Delete (vd);
			ERROR ("varnish plugin: VSM_n_Arg (\"%s\") failed "
					"with status %i.",
					conf->instance, status);
			return (-1);
		}
	}

#if HAVE_VARNISH_V3
	if (VSC_Open (vd, /* diag = */ 1))
#else /* if HAVE_VARNISH_V4 */
	if (VSM_Open (vd))
#endif
	{
		VSM_Delete (vd);
		ERROR ("varnish plugin: Unable to open connection.");

		return (-1);
	}

#if HAVE_VARNISH_V3
	stats = VSC_Main(vd);
#else /* if HAVE_VARNISH_V4 */
	stats = VSC_Main(vd, NULL);
#endif
	if (!stats)
	{
		VSM_Delete (vd);
		ERROR ("varnish plugin: Unable to get statistics.");

		return (-1);
	}

#if HAVE_VARNISH_V3
	VSC_Iter (vd, varnish_monitor, conf);
#else /* if HAVE_VARNISH_V4 */
	VSC_Iter (vd, NULL, varnish_monitor, conf);
#endif
	VSM_Delete (vd);

	return (0);
}