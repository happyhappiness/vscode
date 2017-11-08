static const char *add_ignore_session_id(cmd_parms *parms, void *dummy,
                                         const char *identifier)
{
    cache_server_conf *conf;
    char **new;

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);
    if (!strncasecmp(identifier, "None", 4)) {
        /* if identifier None is listed clear array */
        conf->ignore_session_id->nelts = 0;
    }
    else {
        if ((conf->ignore_session_id_set == CACHE_IGNORE_SESSION_ID_UNSET) ||
            (conf->ignore_session_id->nelts)) {
            /*
             * Only add identifier if no "None" has been found in identifier
             * list so far.
             */
            new = (char **)apr_array_push(conf->ignore_session_id);
            (*new) = (char *)identifier;
        }
    }
    conf->ignore_session_id_set = CACHE_IGNORE_SESSION_ID_SET;
    return NULL;
}