static int varnish_read (user_data_t *ud) /* {{{ */
{
	struct varnish_stats *VSL_stats;
	user_config_t *conf;

	if ((ud == NULL) || (ud->data == NULL))
		return (EINVAL);

	conf = ud->data;

	VSL_stats = VSL_OpenStats (conf->instance);
	if (VSL_stats == NULL)
	{
		ERROR ("Varnish plugin : unable to load statistics");

		return (-1);
	}

	varnish_monitor (conf, VSL_stats);

    return (0);
}