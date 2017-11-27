static int perl_config (oconfig_item_t *ci)
{
	int i = 0;

	dTHXa (NULL);

	for (i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *c = ci->children + i;

		if (NULL != perl_threads)
			aTHX = PERL_GET_CONTEXT;

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