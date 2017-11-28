static void
parse_authparam(authConfig * config)
{
    char *type_str;
    char *param_str;

    if ((type_str = strtok(NULL, w_space)) == NULL)
        self_destruct();

    if ((param_str = strtok(NULL, w_space)) == NULL)
        self_destruct();

    /* find a configuration for the scheme */
    AuthConfig *scheme = AuthConfig::Find (type_str);

    if (scheme == NULL) {
        /* Create a configuration */
        AuthScheme *theScheme;

        if ((theScheme = AuthScheme::Find(type_str)) == NULL) {
            debugs(3, 0, "Parsing Config File: Unknown authentication scheme '" << type_str << "'.");
            return;
        }

        config->push_back(theScheme->createConfig());
        scheme = config->back();
        assert (scheme);
    }

    scheme->parse(scheme, config->size(), param_str);
}