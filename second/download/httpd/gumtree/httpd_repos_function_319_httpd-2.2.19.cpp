static void *dav_merge_dir_config(apr_pool_t *p, void *base, void *overrides)
{
    dav_dir_conf *parent = base;
    dav_dir_conf *child = overrides;
    dav_dir_conf *newconf = (dav_dir_conf *)apr_pcalloc(p, sizeof(*newconf));

    /* DBG3("dav_merge_dir_config: new=%08lx  base=%08lx  overrides=%08lx",
       (long)newconf, (long)base, (long)overrides); */

    newconf->provider_name = DAV_INHERIT_VALUE(parent, child, provider_name);
    newconf->provider = DAV_INHERIT_VALUE(parent, child, provider);
    if (parent->provider_name != NULL) {
        if (child->provider_name == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                         "\"DAV Off\" cannot be used to turn off a subtree "
                         "of a DAV-enabled location.");
        }
        else if (strcasecmp(child->provider_name,
                            parent->provider_name) != 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                         "A subtree cannot specify a different DAV provider "
                         "than its parent.");
        }
    }

    newconf->locktimeout = DAV_INHERIT_VALUE(parent, child, locktimeout);
    newconf->dir = DAV_INHERIT_VALUE(parent, child, dir);
    newconf->allow_depthinfinity = DAV_INHERIT_VALUE(parent, child,
                                                     allow_depthinfinity);

    return newconf;
}