static int display_info(request_rec *r)
{
    module *modp = NULL;
    const char *more_info;
    const command_rec *cmd = NULL;
#ifdef NEVERMORE
    const handler_rec *hand = NULL;
#endif
    server_rec *serv = r->server;
    int comma = 0;

    if (strcmp(r->handler, "server-info"))
        return DECLINED;

    r->allowed |= (AP_METHOD_BIT << M_GET);
    if (r->method_number != M_GET)
	return DECLINED;

    ap_set_content_type(r, "text/html");

    ap_rputs(DOCTYPE_HTML_3_2
	     "<html><head><title>Server Information</title></head>\n", r);
    ap_rputs("<body><h1 align=\"center\">Apache Server Information</h1>\n", r);
    if (!r->args || strcasecmp(r->args, "list")) {
        if (!r->args) {
            ap_rputs("<dl><dt><tt><a href=\"#server\">Server Settings</a>, ", r);
            for (modp = ap_top_module; modp; modp = modp->next) {
                ap_rprintf(r, "<a href=\"#%s\">%s</a>", modp->name, modp->name);
                if (modp->next) {
                    ap_rputs(", ", r);
                }
            }
            ap_rputs("</tt></dt></dl><hr />", r);

        }
        if (!r->args || !strcasecmp(r->args, "server")) {
            int max_daemons, forked, threaded;

            ap_rprintf(r, "<dl><dt><a name=\"server\"><strong>Server Version:</strong> "
                        "<font size=\"+1\"><tt>%s</tt></font></a></dt>\n",
                        ap_get_server_version());
            ap_rprintf(r, "<dt><strong>Server Built:</strong> "
                        "<font size=\"+1\"><tt>%s</tt></font></dt>\n",
                        ap_get_server_built());
            ap_rprintf(r, "<dt><strong>API Version:</strong> "
                        "<tt>%d:%d</tt></dt>\n",
                        MODULE_MAGIC_NUMBER_MAJOR, MODULE_MAGIC_NUMBER_MINOR);
            ap_rprintf(r, "<dt><strong>Hostname/port:</strong> "
                        "<tt>%s:%u</tt></dt>\n",
                        ap_get_server_name(r), ap_get_server_port(r));
            ap_rprintf(r, "<dt><strong>Timeouts:</strong> "
                        "<tt>connection: %d &nbsp;&nbsp; "
                        "keep-alive: %d</tt></dt>",
                        (int)(apr_time_sec(serv->timeout)), 
                        (int)(apr_time_sec(serv->timeout)));
            ap_mpm_query(AP_MPMQ_MAX_DAEMON_USED, &max_daemons);
            ap_mpm_query(AP_MPMQ_IS_THREADED, &threaded);
            ap_mpm_query(AP_MPMQ_IS_FORKED, &forked);
            ap_rprintf(r, "<dt><strong>MPM Name:</strong> <tt>%s</tt></dt>\n", ap_show_mpm());
            ap_rprintf(r, "<dt><strong>MPM Information:</strong> "
		       "<tt>Max Daemons: %d Threaded: %s Forked: %s</tt></dt>\n",
                       max_daemons, threaded ? "yes" : "no",
                       forked ? "yes" : "no");
            ap_rprintf(r, "<dt><strong>Server Root:</strong> "
                        "<tt>%s</tt></dt>\n", ap_server_root);
            ap_rprintf(r, "<dt><strong>Config File:</strong> "
		       "<tt>%s</tt></dt>\n", ap_conftree->filename);
            ap_rputs("</dl><hr />", r);
        }
        for (modp = ap_top_module; modp; modp = modp->next) {
            if (!r->args || !strcasecmp(modp->name, r->args)) {
                ap_rprintf(r, "<dl><dt><a name=\"%s\"><strong>Module Name:</strong> "
                            "<font size=\"+1\"><tt>%s</tt></font></a></dt>\n",
                            modp->name, modp->name);
                ap_rputs("<dt><strong>Content handlers:</strong> ", r);
#ifdef NEVERMORE
                hand = modp->handlers;
                if (hand) {
                    while (hand) {
                        if (hand->content_type) {
                            ap_rprintf(r, " <tt>%s</tt>\n", hand->content_type);
                        }
                        else {
                            break;
                        }
                        hand++;
                        if (hand && hand->content_type) {
                            ap_rputs(",", r);
                        }
                    }
                }
                else {
      