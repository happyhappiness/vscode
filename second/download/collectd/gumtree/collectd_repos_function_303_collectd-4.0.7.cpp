static int pplugin_unregister (int type, char *name)
{
	SV *tmp = NULL;

	if ((type < 0) || (type >= PLUGIN_TYPES))
		return -1;

	if (NULL == name)
		return -1;

	/* freeing the allocated memory of the element itself (pplugin_t *) causes
	 * a segfault during perl_destruct () thus I assume perl somehow takes
	 * care of this... */

	tmp = Perl_hv_delete (perl, plugins[type], name, strlen (name), 0);
	if (NULL != tmp) {
		pplugin_t *p = (pplugin_t *)SvIV ((SV *)SvRV (tmp));
		Perl_sv_free (perl, p->sub);
	}
	return 0;
}