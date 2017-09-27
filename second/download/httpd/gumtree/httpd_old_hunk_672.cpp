        }
        entry++;
    }
    return 0;
}

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

    ap_set_content_type(r, "text/html; charset=ISO-8859-1");

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
                    ap_rputs("<tt> <em>none</em></tt>", r);
                }
#else
                if (module_find_hook(modp, ap_hook_get_handler)) {
                    ap_rputs("<tt> <em>yes</em></tt>", r);
                }
                else {
                    ap_rputs("<tt> <em>none</em></tt>", r);
                }
#endif
                ap_rputs("</dt>", r);
                ap_rputs("<dt><strong>Configuration Phase Participation:</strong>\n",
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
                    ap_rputs("<tt>Create Server Config</tt>", r);
                    comma = 1;
                }
                if (modp->merge_server_config) {
                    if (comma) {
                        ap_rputs(", ", r);
                    }
                    ap_rputs("<tt>Merge Server Configs</tt>", r);
                    comma = 1;
                }
                if (!comma)
                    ap_rputs("<tt> <em>none</em></tt>", r);
                comma = 0;
                ap_rputs("</dt>", r);

                module_request_hook_participate(r, modp);

                cmd = modp->cmds;
                if (cmd) {
                    ap_rputs("<dt><strong>Module Directives:</strong></dt>", r);
                    while (cmd) {
                        if (cmd->name) {
                            ap_rputs("<dd><tt>", r);
                            mod_info_html_cmd_string(r, cmd->name, 0);
                            ap_rputs(" - <i>", r);
                            if (cmd->errmsg) {
                                ap_rputs(cmd->errmsg, r);
                            }
                            ap_rputs("</i></tt></dd>\n", r);
                        }
                        else {
                            break;
                        }
                        cmd++;
                    }
                    ap_rputs("<dt><strong>Current Configuration:</strong></dt>\n", r);
                    mod_info_module_cmds(r, modp->cmds, ap_conftree);
                }
                else {
                    ap_rputs("<dt><strong>Module Directives:</strong> <tt>none</tt></dt>", r);
                }
                more_info = find_more_info(serv, modp->name);
                if (more_info) {
                    ap_rputs("<dt><strong>Additional Information:</strong>\n</dt><dd>",
                          r);
                    ap_rputs(more_info, r);
                    ap_rputs("</dd>", r);
                }
                ap_rputs("</dl><hr />\n", r);
                if (r->args) {
                    break;
                }
            }
        }
        if (!modp && r->args && strcasecmp(r->args, "server")) {
            ap_rputs("<p><b>No such module</b></p>\n", r);
        }
    }
    else {
        ap_rputs("<dl><dt>Server Module List</dt>", r);
        for (modp = ap_top_module; modp; modp = modp->next) {
            ap_rputs("<dd>", r);
            ap_rputs(modp->name, r);
            ap_rputs("</dd>", r);
        }
        ap_rputs("</dl><hr />", r);
    }
    ap_rputs(ap_psignature("",r), r);
    ap_rputs("</body></html>\n", r);
    /* Done, turn off timeout, close file and return */
    return 0;
}

static const char *add_module_info(cmd_parms *cmd, void *dummy, 
                                   const char *name, const char *info)
{
    server_rec *s = cmd->server;
    info_svr_conf *conf = (info_svr_conf *) ap_get_module_config(s->module_config,
                                                              &info_module);
    info_entry *new = apr_array_push(conf->more_info);

    new->name = name;
    new->info = info;
    return NULL;
}

static const command_rec info_cmds[] =
{
    AP_INIT_TAKE2("AddModuleInfo", add_module_info, NULL, RSRC_CONF,
                  "a module name and additional information on that module"),
    {NULL}
};

static void register_hooks(apr_pool_t *p)
{
    ap_hook_handler(display_info, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA info_module =
{
    STANDARD20_MODULE_STUFF,
    NULL,                       /* dir config creater */
    NULL,                       /* dir merger --- default is to override */
    create_info_config,         /* server config */
    merge_info_config,          /* merge server config */
    info_cmds,                  /* command apr_table_t */
