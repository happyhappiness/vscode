       (long)newconf, (long)base, (long)overrides); */

    newconf->provider_name = DAV_INHERIT_VALUE(parent, child, provider_name);
    newconf->provider = DAV_INHERIT_VALUE(parent, child, provider);
    if (parent->provider_name != NULL) {
        if (child->provider_name == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, APLOGNO(00578)
                         "\"DAV Off\" cannot be used to turn off a subtree "
                         "of a DAV-enabled location.");
        }
        else if (strcasecmp(child->provider_name,
                            parent->provider_name) != 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, APLOGNO(00579)
                         "A subtree cannot specify a different DAV provider "
                         "than its parent.");
        }
    }

    newconf->locktimeout = DAV_INHERIT_VALUE(parent, child, locktimeout);
