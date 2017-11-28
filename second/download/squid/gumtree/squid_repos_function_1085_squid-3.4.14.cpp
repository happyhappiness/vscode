static void
parse_authparam(Auth::ConfigVector * config)
{
    char *type_str;
    char *param_str;

    if ((type_str = strtok(NULL, w_space)) == NULL)
        self_destruct();

    if ((param_str = strtok(NULL, w_space)) == NULL)
        self_destruct();

    /* find a configuration for the scheme in the currently parsed configs... */
    Auth::Config *schemeCfg = Auth::Config::Find(type_str);

    if (schemeCfg == NULL) {
        /* Create a configuration based on the scheme info */
        Auth::Scheme::Pointer theScheme = Auth::Scheme::Find(type_str);

        if (theScheme == NULL) {
            debugs(3, DBG_CRITICAL, "Parsing Config File: Unknown authentication scheme '" << type_str << "'.");
            self_destruct();
        }

        config->push_back(theScheme->createConfig());
        schemeCfg = Auth::Config::Find(type_str);
        if (schemeCfg == NULL) {
            debugs(3, DBG_CRITICAL, "Parsing Config File: Corruption configuring authentication scheme '" << type_str << "'.");
            self_destruct();
        }
    }

    schemeCfg->parse(schemeCfg, config->size(), param_str);
}