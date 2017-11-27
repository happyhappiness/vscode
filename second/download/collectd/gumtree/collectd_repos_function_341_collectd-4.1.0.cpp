static int pplugin_unregister_data_set (char *name)
{
	SV *tmp = NULL;

	if (NULL == name)
		return 0;

	/* freeing the allocated memory of the element itself (ds_types_t *)
	 * causes a segfault during perl_destruct () thus I assume perl somehow
	 * takes care of this... */

	tmp = Perl_hv_delete (perl, data_sets, name, strlen (name), 0);
	if (NULL != tmp) {
		ds_types_t *ds = (ds_types_t *)SvIV ((SV *)SvRV (tmp));
		sfree (ds->values);
	}
	return plugin_unregister_data_set (name);
}