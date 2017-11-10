static int display_info(request_rec * r)
{
    module *modp = NULL;
    server_rec *serv = r->server;
    const char *more_info;
    const command_rec *cmd = NULL;
    int comma = 0;

    if (strcmp(r->handler, "server-info"))
        return DECLINED;

    r->allowed |= (AP_METHOD_BIT << M_GET);
    if (r->method_number != M_GET)
        return DECLINED;

    ap_set_content_type(r, "text/html");

    ap_rputs(DOCTYPE_XHTML_1_0T
             "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
             "<head>\n"
             "  <title>Server Information</title>\n" "</head>\n", r);
    ap_rputs("<body><h1 style=\"text-align: center\">"
             "Apache Server Information</h1>\n", r);
    if (!r->args || strcasecmp(r->args, "list")) {
        if (!r->args) {
            ap_rputs("<dl><dt><tt>Subpages:<br />", r);
            ap_rputs("<a href=\"?config\">Configuration Files</a>, "
                     "<a href=\"?server\">Server Settings</a>, "
                     "<a href=\"?list\">Module List</a>,  "
                     "<a href=\"?hooks\">Active Hooks</a>", r);
            ap_rputs("</tt></dt></dl><hr />", r);

            ap_rputs("<dl><dt><tt>Sections:<br />", r);
            ap_rputs("<a href=\"#server\">Server Settings</a>, "
                     "<a href=\"#startup_hooks\">Startup Hooks</a>, "
                     "<a href=\"#request_hooks\">Request Hooks</a>", r);
            ap_rputs("</tt></dt></dl><hr />", r);

            ap_rputs("<dl><dt><tt>Loaded Modules: <br />", r);
            /* TODO: Sort by Alpha */
            for (modp = ap_top_module; modp; modp = modp->next) {
                ap_rprintf(r, "<a href=\"#%s\">%s</a>", modp->name,
                           modp->name);
                if (modp->next) {
                    ap_rputs(", ", r);
                }
            }
            ap_rputs("</tt></dt></dl><hr />", r);
        }

        if (!r->args || !strcasecmp(r->args, "server")) {
            show_server_settings(r);
        }

        if (!r->args || !strcasecmp(r->args, "hooks")) {
            show_active_hooks(r);
        }

        if (r->args && 0 == strcasecmp(r->args, "config")) {
            ap_rputs("<dl><dt><strong>Configuration:</strong>\n", r);
            mod_info_module_cmds(r, NULL, ap_conftree, 0, 0);
            ap_rputs("</dl><hr />", r);
        }
        else {
            for (modp = ap_top_module; modp; modp = modp->next) {
                if (!r->args || !strcasecmp(modp->name, r->args)) {
                    ap_rprintf(r,
                               "<dl><dt><a name=\"%s\"><strong>Module Name:</strong></a> "
                               "<font size=\"+1\"><tt><a href=\"?%s\">%s</a></tt></font></dt>\n",
                               modp->name, modp->name, modp->name);
                    ap_rputs("<dt><strong>Content handlers:</strong> ", r);

                    if (module_find_hook(modp, ap_hook_get_handler)) {
                        ap_rputs("<tt> <em>yes</em></tt>", r);
                    }
                    else {
                        ap_rputs("<tt> <em>none</em></tt>", r);
                    }

                    ap_rputs("</dt>", r);
                    ap_rputs
                        ("<dt><strong>Configuration Phase Participation:</strong>\n",
                         r);
                    if (modp->create_dir_config) {
                        if (comma) {
                            ap_rputs(", ", r);
                        }
                        ap_rputs("<tt>Create Directory Config</tt>", r);
                        comma = 1;
                    }
                    if (modp->merge_dir_config) {
                        if (comma) {
                            ap_rputs(", ", r);
                        }
                        ap_rputs("<tt>Merge Directory Configs</tt>", r);
                        comma = 1;
                    }
                    if (modp->create_server_config) {
                        if (comma) {
                            ap_rputs(", ", r);
                        }
                        ap_rputs("