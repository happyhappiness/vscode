static int varnish_init (void) /* {{{ */
{
	user_config_t *conf;

	if (have_instance)
		return (0);

	conf = calloc (1, sizeof (*conf));
	if (conf == NULL)
		return (ENOMEM);

	/* Default settings: */
	conf->instance = NULL;

	varnish_config_apply_default (conf);

	user_data_t ud = {
		.data = conf,
		.free_func = varnish_config_free
	};

	plugin_register_complex_read (/* group = */ "varnish",
			/* name      = */ "varnish/localhost",
			/* callback  = */ varnish_read,
			/* interval  = */ 0,
			/* user data = */ &ud);

	return (0);
}