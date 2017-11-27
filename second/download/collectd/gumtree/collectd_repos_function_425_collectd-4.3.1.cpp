static int perl_config (oconfig_item_t *ci)
{
	int i = 0;

	dTHX;

	/* dTHX does not get any valid values in case Perl
	 * has not been initialized */
	if (NULL == perl_threads)
		aTHX = NULL;

	for (i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *c = ci->children + i;

		if (0 == strcasecmp (c->key, "LoadPlugin"))
			perl_config_loadplugin (aTHX_ c);
		else if (0 == strcasecmp (c->key, "BaseName"))
			perl_config_basename (aTHX_ c);
		else if (0 == strcasecmp (c->key, "EnableDebugger"))
			perl_config_enabledebugger (aTHX_ c);
		else if (0 == strcasecmp (c->key, "IncludeDir"))
			perl_config_includedir (aTHX_ c);
		else
			log_warn ("Ignoring unknown config key \"%s\".", c->key);
	}
	return 0;
}