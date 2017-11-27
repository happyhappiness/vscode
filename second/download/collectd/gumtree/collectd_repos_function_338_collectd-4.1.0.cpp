static int pplugin_register (int type, const char *name, SV *sub)
{
	pplugin_t *p = NULL;

	if ((type < 0) || (type >= PLUGIN_TYPES))
		return -1;

	if (NULL == name)
		return -1;

	p = (pplugin_t *)smalloc (sizeof (pplugin_t));
	/* this happens during parsing of config file,
	 * thus interval_g is not set correctly */
	p->wait_time = 10;
	p->wait_left = 0;
	p->sub = Perl_newSVsv (perl, sub);

	if (NULL == Perl_hv_store (perl, plugins[type], name, strlen (name),
				Perl_sv_setref_pv (perl, Perl_newSV (perl, 0), 0, p), 0)) {
		log_debug ("pplugin_register: Failed to add plugin \"%s\" (\"%s\")",
				name, SvPV_nolen (sub));
		Perl_sv_free (perl, p->sub);
		sfree (p);
		return -1;
	}
	return 0;
}