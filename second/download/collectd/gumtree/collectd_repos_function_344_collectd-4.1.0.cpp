static int pplugin_call_all (int type, ...)
{
	SV *tmp = NULL;

	char *plugin;
	I32  len;

	if ((type < 0) || (type >= PLUGIN_TYPES))
		return -1;

	if (0 == Perl_hv_iterinit (perl, plugins[type]))
		return 0;

	while (NULL != (tmp = Perl_hv_iternextsv (perl, plugins[type],
			&plugin, &len))) {
		pplugin_t *p;
		va_list   ap;

		int status;

		va_start (ap, type);

		p = (pplugin_t *)SvIV ((SV *)SvRV (tmp));

		if (p->wait_left > 0)
			p->wait_left -= interval_g;

		if (p->wait_left > 0)
			continue;

		if (0 == (status = pplugin_call (type, plugin, p->sub, ap))) {
			p->wait_left = 0;
			p->wait_time = interval_g;
		}
		else if (PLUGIN_READ == type) {
			p->wait_left = p->wait_time;
			p->wait_time <<= 1;

			if (p->wait_time > 86400)
				p->wait_time = 86400;

			log_warn ("%s->read() failed. Will suspend it for %i seconds.",
					plugin, p->wait_left);
		}
		else if (PLUGIN_INIT == type) {
			int i = 0;

			log_err ("%s->init() failed. Plugin will be disabled.",
					plugin, status);

			for (i = 0; i < PLUGIN_TYPES; ++i)
				pplugin_unregister (i, plugin);
		}
		else if (PLUGIN_LOG != type) {
			log_warn ("%s->%s() failed with status %i.",
					plugin, plugin_types[type], status);
		}

		va_end (ap);
	}
	return 0;
}