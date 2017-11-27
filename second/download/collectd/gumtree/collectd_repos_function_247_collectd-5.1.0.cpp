static int varnish_read (user_data_t *ud) /* {{{ */
{
	struct VSM_data *vd;
	const c_varnish_stats_t *stats;

	user_config_t *conf;

	if ((ud == NULL) || (ud->data == NULL))
		return (EINVAL);

	conf = ud->data;

	vd = VSM_New();
	VSC_Setup(vd);
	if (VSC_Open (vd, /* diag = */ 1))
	{
		ERROR ("varnish plugin: Unable to load statistics.");

		return (-1);
	}

	stats = VSC_Main(vd);

	varnish_monitor (conf, stats);
	VSM_Close (vd);

	return (0);
}