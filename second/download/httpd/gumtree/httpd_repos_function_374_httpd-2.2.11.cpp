static int dav_fixups(request_rec *r)
{
    dav_dir_conf *conf;

    /* quickly ignore any HTTP/0.9 requests which aren't subreqs. */
    if (r->assbackwards && !r->main) {
        return DECLINED;
    }

    conf = (dav_dir_conf *)ap_get_module_config(r->per_dir_config,
                                                &dav_module);

    /* if DAV is not enabled, then we've got nothing to do */
    if (conf->provider == NULL) {
        return DECLINED;
    }

    /* We are going to handle almost every request. In certain cases,
       the provider maps to the filesystem (thus, handle_get is
       FALSE), and core Apache will handle it. a For that case, we
       just return right away.  */
    if (r->method_number == M_GET) {
        /*
         * ### need some work to pull Content-Type and Content-Language
         * ### from the property database.
         */

        /*
         * If the repository hasn't indicated that it will handle the
         * GET method, then just punt.
         *
         * ### this isn't quite right... taking over the response can break
         * ### things like mod_negotiation. need to look into this some more.
         */
        if (!conf->provider->repos->handle_get) {
            return DECLINED;
        }
    }

    /* ### this is wrong.  We should only be setting the r->handler for the
     * requests that mod_dav knows about.  If we set the handler for M_POST
     * requests, then CGI scripts that use POST will return the source for the
     * script.  However, mod_dav DOES handle POST, so something else needs
     * to be fixed.
     */
    if (r->method_number != M_POST) {

        /* We are going to be handling the response for this resource. */
        r->handler = DAV_HANDLER_NAME;
        return OK;
    }

    return DECLINED;
}