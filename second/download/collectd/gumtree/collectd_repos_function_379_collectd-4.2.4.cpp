static int perl_config (oconfig_item_t *ci)
{
	int i = 0;

	for (i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *c = ci->children + i;

		if (0 == strcasecmp (c->key, "LoadPlugin"))
			perl_config_loadplugin (c);
		else if (0 == strcasecmp (c->key, "BaseName"))
			perl_config_basename (c);
		else if (0 == strcasecmp (c->key, "EnableDebugger"))
			perl_config_enabledebugger (c);
		else if (0 == strcasecmp (c->key, "IncludeDir"))
			perl_config_includedir (c);
		else
			log_warn ("Ignoring unknown config key \"%s\".", c->key);
	}
	return 0;
}