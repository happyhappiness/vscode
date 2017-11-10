static int include_fixup(request_rec *r)
{
    if (r->handler && (strcmp(r->handler, "server-parsed") == 0))
    {
        if (!r->content_type || !*r->content_type) {
            ap_set_content_type(r, "text/html");
        }
        r->handler = "default-handler";
    }
    else
#if defined(OS2) || defined(WIN32) || defined(NETWARE)
    /* These OS's don't support xbithack. This is being worked on. */
    {
        return DECLINED;
    }
#else
    {
        include_dir_config *conf = ap_get_module_config(r->per_dir_config,
                                                        &include_module);

        if (conf->xbithack == XBITHACK_OFF ||
            (DEFAULT_XBITHACK == XBITHACK_OFF &&
             conf->xbithack == XBITHACK_UNSET))
        {
            return DECLINED;
        }

        if (!(r->finfo.protection & APR_UEXECUTE)) {
            return DECLINED;
        }

        if (!r->content_type || strncmp(r->content_type, "text/html", 9)) {
            return DECLINED;
        }
    }
#endif

    /* We always return declined, because the default handler actually
     * serves the file.  All we have to do is add the filter.
     */
    ap_add_output_filter("INCLUDES", NULL, r, r->connection);
    return DECLINED;
}