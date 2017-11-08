static const char *add_ignore_header(cmd_parms *parms, void *dummy,
                                     const char *header)
{
    cache_server_conf *conf;
    char **new;

    conf =
        (cache_server_conf *)ap_get_module_config(parms->server->module_config,
                                                  &cache_module);
    if (!strncasecmp(header, "None", 4)) {
        /* if header None is listed clear array */
        conf->ignore_headers->nelts = 0;
    }
    else {
        if ((conf->ignore_headers_set == CACHE_IGNORE_HEADERS_UNSET) ||
            (conf->ignore_headers->nelts)) {
            /* Only add header if no "None" has been found in header list
             * so far.
             * (When 'None' is passed, IGNORE_HEADERS_SET && nelts == 0.)
             */
            new = (char **)apr_array_push(conf->ignore_headers);
            (*new) = (char*)header;
        }
    }
    conf->ignore_headers_set = CACHE_IGNORE_HEADERS_SET;
    return NULL;
}