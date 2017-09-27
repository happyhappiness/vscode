         }
         entry++;
     }
     return 0;
 }
 
-static int display_info(request_rec *r)
+static int show_server_settings(request_rec * r)
+{
+    server_rec *serv = r->server;
+    int max_daemons, forked, threaded;
+
+    ap_rputs("<h2><a name=\"server\">Server Settings</a></h2>", r);
+    ap_rprintf(r,
+               "<dl><dt><strong>Server Version:</strong> "
+               "<font size=\"+1\"><tt>%s</tt></font></dt>\n",
+               ap_get_server_version());
+    ap_rprintf(r,
+               "<dt><strong>Server Built:</strong> "
+               "<font size=\"+1\"><tt>%s</tt></font></dt>\n",
+               ap_get_server_built());
+    ap_rprintf(r,
+               "<dt><strong>Module Magic Number:</strong> "
+               "<tt>%d:%d</tt></dt>\n", MODULE_MAGIC_NUMBER_MAJOR,
+               MODULE_MAGIC_NUMBER_MINOR);
+    ap_rprintf(r,
+               "<dt><strong>Hostname/port:</strong> "
+               "<tt>%s:%u</tt></dt>\n", ap_get_server_name(r),
+               ap_get_server_port(r));
+    ap_rprintf(r,
+               "<dt><strong>Timeouts:</strong> "
+               "<tt>connection: %d &nbsp;&nbsp; "
+               "keep-alive: %d</tt></dt>",
+               (int) (apr_time_sec(serv->timeout)),
+               (int) (apr_time_sec(serv->timeout)));
+    ap_mpm_query(AP_MPMQ_MAX_DAEMON_USED, &max_daemons);
+    ap_mpm_query(AP_MPMQ_IS_THREADED, &threaded);
+    ap_mpm_query(AP_MPMQ_IS_FORKED, &forked);
+    ap_rprintf(r, "<dt><strong>MPM Name:</strong> <tt>%s</tt></dt>\n",
+               ap_show_mpm());
+    ap_rprintf(r,
+               "<dt><strong>MPM Information:</strong> "
+               "<tt>Max Daemons: %d Threaded: %s Forked: %s</tt></dt>\n",
+               max_daemons, threaded ? "yes" : "no", forked ? "yes" : "no");
+    ap_rprintf(r,
+               "<dt><strong>Server Architecture:</strong> "
+               "<tt>%ld-bit</tt></dt>\n", 8 * (long) sizeof(void *));
+    ap_rprintf(r,
+               "<dt><strong>Server Root:</strong> "
+               "<tt>%s</tt></dt>\n", ap_server_root);
+    ap_rprintf(r,
+               "<dt><strong>Config File:</strong> "
+               "<tt>%s</tt></dt>\n", ap_conftree->filename);
+
+    ap_rputs("<dt><strong>Server Built With:</strong>\n"
+             "<tt style=\"white-space: pre;\">\n", r);
+
+    /* TODO: Not all of these defines are getting set like they do in main.c.
+     *       Missing some headers?
+     */
+
+#ifdef BIG_SECURITY_HOLE
+    ap_rputs(" -D BIG_SECURITY_HOLE\n", r);
+#endif
+
+#ifdef SECURITY_HOLE_PASS_AUTHORIZATION
+    ap_rputs(" -D SECURITY_HOLE_PASS_AUTHORIZATION\n", r);
+#endif
+
+#ifdef OS
+    ap_rputs(" -D OS=\"" OS "\"\n", r);
+#endif
+
+#ifdef APACHE_MPM_DIR
+    ap_rputs(" -D APACHE_MPM_DIR=\"" APACHE_MPM_DIR "\"\n", r);
+#endif
+
+#ifdef HAVE_SHMGET
+    ap_rputs(" -D HAVE_SHMGET\n", r);
+#endif
+
+#if APR_FILE_BASED_SHM
+    ap_rputs(" -D APR_FILE_BASED_SHM\n", r);
+#endif
+
+#if APR_HAS_SENDFILE
+    ap_rputs(" -D APR_HAS_SENDFILE\n", r);
+#endif
+
+#if APR_HAS_MMAP
+    ap_rputs(" -D APR_HAS_MMAP\n", r);
+#endif
+
+#ifdef NO_WRITEV
+    ap_rputs(" -D NO_WRITEV\n", r);
+#endif
+
+#ifdef NO_LINGCLOSE
+    ap_rputs(" -D NO_LINGCLOSE\n", r);
+#endif
+
+#if APR_HAVE_IPV6
+    ap_rputs(" -D APR_HAVE_IPV6 (IPv4-mapped addresses ", r);
+#ifdef AP_ENABLE_V4_MAPPED
+    ap_rputs("enabled)\n", r);
+#else
+    ap_rputs("disabled)\n", r);
+#endif
+#endif
+
+#if APR_USE_FLOCK_SERIALIZE
+    ap_rputs(" -D APR_USE_FLOCK_SERIALIZE\n", r);
+#endif
+
+#if APR_USE_SYSVSEM_SERIALIZE
+    ap_rputs(" -D APR_USE_SYSVSEM_SERIALIZE\n", r);
+#endif
+
+#if APR_USE_POSIXSEM_SERIALIZE
+    ap_rputs(" -D APR_USE_POSIXSEM_SERIALIZE\n", r);
+#endif
+
+#if APR_USE_FCNTL_SERIALIZE
+    ap_rputs(" -D APR_USE_FCNTL_SERIALIZE\n", r);
+#endif
+
+#if APR_USE_PROC_PTHREAD_SERIALIZE
+    ap_rputs(" -D APR_USE_PROC_PTHREAD_SERIALIZE\n", r);
+#endif
+#if APR_PROCESS_LOCK_IS_GLOBAL
+    ap_rputs(" -D APR_PROCESS_LOCK_IS_GLOBAL\n", r);
+#endif
+
+#ifdef SINGLE_LISTEN_UNSERIALIZED_ACCEPT
+    ap_rputs(" -D SINGLE_LISTEN_UNSERIALIZED_ACCEPT\n", r);
+#endif
+
+#if APR_HAS_OTHER_CHILD
+    ap_rputs(" -D APR_HAS_OTHER_CHILD\n", r);
+#endif
+
+#ifdef AP_HAVE_RELIABLE_PIPED_LOGS
+    ap_rputs(" -D AP_HAVE_RELIABLE_PIPED_LOGS\n", r);
+#endif
+
+#ifdef BUFFERED_LOGS
+    ap_rputs(" -D BUFFERED_LOGS\n", r);
+#ifdef PIPE_BUF
+    ap_rputs(" -D PIPE_BUF=%ld\n", (long) PIPE_BUF, r);
+#endif
+#endif
+
+#if APR_CHARSET_EBCDIC
+    ap_rputs(" -D APR_CHARSET_EBCDIC\n", r);
+#endif
+
+#ifdef NEED_HASHBANG_EMUL
+    ap_rputs(" -D NEED_HASHBANG_EMUL\n", r);
+#endif
+
+#ifdef SHARED_CORE
+    ap_rputs(" -D SHARED_CORE\n", r);
+#endif
+
+/* This list displays the compiled in default paths: */
+#ifdef HTTPD_ROOT
+    ap_rputs(" -D HTTPD_ROOT=\"" HTTPD_ROOT "\"\n", r);
+#endif
+
+#ifdef SUEXEC_BIN
+    ap_rputs(" -D SUEXEC_BIN=\"" SUEXEC_BIN "\"\n", r);
+#endif
+
+#if defined(SHARED_CORE) && defined(SHARED_CORE_DIR)
+    ap_rputs(" -D SHARED_CORE_DIR=\"" SHARED_CORE_DIR "\"\n", r);
+#endif
+
+#ifdef DEFAULT_PIDLOG
+    ap_rputs(" -D DEFAULT_PIDLOG=\"" DEFAULT_PIDLOG "\"\n", r);
+#endif
+
+#ifdef DEFAULT_SCOREBOARD
+    ap_rputs(" -D DEFAULT_SCOREBOARD=\"" DEFAULT_SCOREBOARD "\"\n", r);
+#endif
+
+#ifdef DEFAULT_LOCKFILE
+    ap_rputs(" -D DEFAULT_LOCKFILE=\"" DEFAULT_LOCKFILE "\"\n", r);
+#endif
+
+#ifdef DEFAULT_ERRORLOG
+    ap_rputs(" -D DEFAULT_ERRORLOG=\"" DEFAULT_ERRORLOG "\"\n", r);
+#endif
+
+
+#ifdef AP_TYPES_CONFIG_FILE
+    ap_rputs(" -D AP_TYPES_CONFIG_FILE=\"" AP_TYPES_CONFIG_FILE "\"\n", r);
+#endif
+
+#ifdef SERVER_CONFIG_FILE
+    ap_rputs(" -D SERVER_CONFIG_FILE=\"" SERVER_CONFIG_FILE "\"\n", r);
+#endif
+    ap_rputs("</tt></dt>\n", r);
+    ap_rputs("</dl><hr />", r);
+    return 0;
+}
+
+static int dump_a_hook(request_rec * r, hook_get_t hook_get)
+{
+    int i;
+    char qs;
+    hook_struct_t *elts;
+    apr_array_header_t *hooks = hook_get();
+
+    if (!hooks) {
+        return 0;
+    }
+
+    if (r->args && strcasecmp(r->args, "hooks") == 0) {
+        qs = '?';
+    }
+    else {
+        qs = '#';
+    }
+
+    elts = (hook_struct_t *) hooks->elts;
+
+    for (i = 0; i < hooks->nelts; i++) {
+        ap_rprintf(r,
+                   "&nbsp;&nbsp; %02d <a href=\"%c%s\">%s</a> <br/>",
+                   elts[i].nOrder, qs, elts[i].szName, elts[i].szName);
+    }
+    return 0;
+}
+
+static int show_active_hooks(request_rec * r)
+{
+    int i;
+    ap_rputs("<h2><a name=\"startup_hooks\">Startup Hooks</a></h2>\n<dl>", r);
+
+    for (i = 0; startup_hooks[i].name; i++) {
+        ap_rprintf(r, "<dt><strong>%s:</strong>\n <br /><tt>\n",
+                   startup_hooks[i].name);
+        dump_a_hook(r, startup_hooks[i].get);
+        ap_rputs("\n  </tt>\n</dt>\n", r);
+    }
+
+    ap_rputs
+        ("</dl>\n<hr />\n<h2><a name=\"request_hooks\">Request Hooks</a></h2>\n<dl>",
+         r);
+
+    for (i = 0; request_hooks[i].name; i++) {
+        ap_rprintf(r, "<dt><strong>%s:</strong>\n <br /><tt>\n",
+                   request_hooks[i].name);
+        dump_a_hook(r, request_hooks[i].get);
+        ap_rputs("\n  </tt>\n</dt>\n", r);
+    }
+
+    ap_rputs("</dl>\n<hr />\n", r);
+
+    return 0;
+}
+
+static int display_info(request_rec * r)
 {
     module *modp = NULL;
+    server_rec *serv = r->server;
     const char *more_info;
     const command_rec *cmd = NULL;
-#ifdef NEVERMORE
-    const handler_rec *hand = NULL;
-#endif
-    server_rec *serv = r->server;
     int comma = 0;
 
     if (strcmp(r->handler, "server-info"))
         return DECLINED;
 
     r->allowed |= (AP_METHOD_BIT << M_GET);
     if (r->method_number != M_GET)
 	return DECLINED;
 
-    ap_set_content_type(r, "text/html; charset=ISO-8859-1");
+    ap_set_content_type(r, "text/html");
 
-    ap_rputs(DOCTYPE_HTML_3_2
-	     "<html><head><title>Server Information</title></head>\n", r);
-    ap_rputs("<body><h1 align=\"center\">Apache Server Information</h1>\n", r);
+    ap_rputs(DOCTYPE_XHTML_1_0T
+             "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
+             "<head>\n"
+             "  <title>Server Information</title>\n" "</head>\n", r);
+    ap_rputs("<body><h1 style=\"text-align: center\">"
+             "Apache Server Information</h1>\n", r);
     if (!r->args || strcasecmp(r->args, "list")) {
         if (!r->args) {
-            ap_rputs("<dl><dt><tt><a href=\"#server\">Server Settings</a>, ", r);
+            ap_rputs("<dl><dt><tt>Subpages:<br />", r);
+            ap_rputs("<a href=\"?config\">Configuration Files</a>, "
+                     "<a href=\"?server\">Server Settings</a>, "
+                     "<a href=\"?list\">Module List</a>,  "
+                     "<a href=\"?hooks\">Active Hooks</a>", r);
+            ap_rputs("</tt></dt></dl><hr />", r);
+
+            ap_rputs("<dl><dt><tt>Sections:<br />", r);
+            ap_rputs("<a href=\"#server\">Server Settings</a>, "
+                     "<a href=\"#startup_hooks\">Startup Hooks</a>, "
+                     "<a href=\"#request_hooks\">Request Hooks</a>", r);
+            ap_rputs("</tt></dt></dl><hr />", r);
+
+            ap_rputs("<dl><dt><tt>Loaded Modules: <br />", r);
+            /* TODO: Sort by Alpha */
             for (modp = ap_top_module; modp; modp = modp->next) {
-                ap_rprintf(r, "<a href=\"#%s\">%s</a>", modp->name, modp->name);
+                ap_rprintf(r, "<a href=\"#%s\">%s</a>", modp->name,
+                           modp->name);
                 if (modp->next) {
                     ap_rputs(", ", r);
                 }
             }
             ap_rputs("</tt></dt></dl><hr />", r);
-
         }
+
         if (!r->args || !strcasecmp(r->args, "server")) {
-            int max_daemons, forked, threaded;
+            show_server_settings(r);
+        }
 
-            ap_rprintf(r, "<dl><dt><a name=\"server\"><strong>Server Version:</strong> "
-                        "<font size=\"+1\"><tt>%s</tt></font></a></dt>\n",
-                        ap_get_server_version());
-            ap_rprintf(r, "<dt><strong>Server Built:</strong> "
-                        "<font size=\"+1\"><tt>%s</tt></font></dt>\n",
-                        ap_get_server_built());
-            ap_rprintf(r, "<dt><strong>API Version:</strong> "
-                        "<tt>%d:%d</tt></dt>\n",
-                        MODULE_MAGIC_NUMBER_MAJOR, MODULE_MAGIC_NUMBER_MINOR);
-            ap_rprintf(r, "<dt><strong>Hostname/port:</strong> "
-                        "<tt>%s:%u</tt></dt>\n",
-                        ap_get_server_name(r), ap_get_server_port(r));
-            ap_rprintf(r, "<dt><strong>Timeouts:</strong> "
-                        "<tt>connection: %d &nbsp;&nbsp; "
-                        "keep-alive: %d</tt></dt>",
-                        (int)(apr_time_sec(serv->timeout)), 
-                        (int)(apr_time_sec(serv->timeout)));
-            ap_mpm_query(AP_MPMQ_MAX_DAEMON_USED, &max_daemons);
-            ap_mpm_query(AP_MPMQ_IS_THREADED, &threaded);
-            ap_mpm_query(AP_MPMQ_IS_FORKED, &forked);
-            ap_rprintf(r, "<dt><strong>MPM Name:</strong> <tt>%s</tt></dt>\n", ap_show_mpm());
-            ap_rprintf(r, "<dt><strong>MPM Information:</strong> "
-		       "<tt>Max Daemons: %d Threaded: %s Forked: %s</tt></dt>\n",
-                       max_daemons, threaded ? "yes" : "no",
-                       forked ? "yes" : "no");
-            ap_rprintf(r, "<dt><strong>Server Root:</strong> "
-                        "<tt>%s</tt></dt>\n", ap_server_root);
-            ap_rprintf(r, "<dt><strong>Config File:</strong> "
-		       "<tt>%s</tt></dt>\n", ap_conftree->filename);
+        if (!r->args || !strcasecmp(r->args, "hooks")) {
+            show_active_hooks(r);
+        }
+
+        if (r->args && 0 == strcasecmp(r->args, "config")) {
+            ap_rputs("<dl><dt><strong>Configuration:</strong>\n", r);
+            mod_info_module_cmds(r, NULL, ap_conftree, 0, 0);
             ap_rputs("</dl><hr />", r);
         }
-        for (modp = ap_top_module; modp; modp = modp->next) {
-            if (!r->args || !strcasecmp(modp->name, r->args)) {
-                ap_rprintf(r, "<dl><dt><a name=\"%s\"><strong>Module Name:</strong> "
-                            "<font size=\"+1\"><tt>%s</tt></font></a></dt>\n",
-                            modp->name, modp->name);
-                ap_rputs("<dt><strong>Content handlers:</strong> ", r);
-#ifdef NEVERMORE
-                hand = modp->handlers;
-                if (hand) {
-                    while (hand) {
-                        if (hand->content_type) {
-                            ap_rprintf(r, " <tt>%s</tt>\n", hand->content_type);
+        else {
+            for (modp = ap_top_module; modp; modp = modp->next) {
+                if (!r->args || !strcasecmp(modp->name, r->args)) {
+                    ap_rprintf(r,
+                               "<dl><dt><a name=\"%s\"><strong>Module Name:</strong></a> "
+                               "<font size=\"+1\"><tt><a href=\"?%s\">%s</a></tt></font></dt>\n",
+                               modp->name, modp->name, modp->name);
+                    ap_rputs("<dt><strong>Content handlers:</strong> ", r);
+
+                    if (module_find_hook(modp, ap_hook_get_handler)) {
+                        ap_rputs("<tt> <em>yes</em></tt>", r);
+                    }
+                    else {
+                        ap_rputs("<tt> <em>none</em></tt>", r);
+                    }
+
+                    ap_rputs("</dt>", r);
+                    ap_rputs
+                        ("<dt><strong>Configuration Phase Participation:</strong>\n",
+                         r);
+                    if (modp->create_dir_config) {
+                        if (comma) {
+                            ap_rputs(", ", r);
                         }
-                        else {
-                            break;
+                        ap_rputs("<tt>Create Directory Config</tt>", r);
+                        comma = 1;
+                    }
+                    if (modp->merge_dir_config) {
+                        if (comma) {
+                            ap_rputs(", ", r);
                         }
-                        hand++;
-                        if (hand && hand->content_type) {
-                            ap_rputs(",", r);
+                        ap_rputs("<tt>Merge Directory Configs</tt>", r);
+                        comma = 1;
+                    }
+                    if (modp->create_server_config) {
+                        if (comma) {
+                            ap_rputs(", ", r);
                         }
+                        ap_rputs("<tt>Create Server Config</tt>", r);
+                        comma = 1;
                     }
-                }
-                else {
-                    ap_rputs("<tt> <em>none</em></tt>", r);
-                }
-#else
-                if (module_find_hook(modp, ap_hook_get_handler)) {
-                    ap_rputs("<tt> <em>yes</em></tt>", r);
-                }
-                else {
-                    ap_rputs("<tt> <em>none</em></tt>", r);
-                }
-#endif
-                ap_rputs("</dt>", r);
-                ap_rputs("<dt><strong>Configuration Phase Participation:</strong>\n",
-                      r);
-                if (modp->create_dir_config) {
-                    if (comma) {
-                        ap_rputs(", ", r);
+                    if (modp->merge_server_config) {
+                        if (comma) {
+                            ap_rputs(", ", r);
+                        }
+                        ap_rputs("<tt>Merge Server Configs</tt>", r);
+                        comma = 1;
                     }
-                    ap_rputs("<tt>Create Directory Config</tt>", r);
-                    comma = 1;
-                }
-                if (modp->merge_dir_config) {
-                    if (comma) {
-                        ap_rputs(", ", r);
+                    if (!comma)
+                        ap_rputs("<tt> <em>none</em></tt>", r);
+                    comma = 0;
+                    ap_rputs("</dt>", r);
+
+                    module_request_hook_participate(r, modp);
+
+                    cmd = modp->cmds;
+                    if (cmd) {
+                        ap_rputs
+                            ("<dt><strong>Module Directives:</strong></dt>",
+                             r);
+                        while (cmd) {
+                            if (cmd->name) {
+                                ap_rprintf(r, "<dd><tt>%s%s - <i>",
+                                           ap_escape_html(r->pool, cmd->name),
+                                           cmd->name[0] == '<' ? "&gt;" : "");
+                                if (cmd->errmsg) {
+                                    ap_rputs(cmd->errmsg, r);
+                                }
+                                ap_rputs("</i></tt></dd>\n", r);
+                            }
+                            else {
+                                break;
+                            }
+                            cmd++;
+                        }
+                        ap_rputs
+                            ("<dt><strong>Current Configuration:</strong></dt>\n",
+                             r);
+                        mod_info_module_cmds(r, modp->cmds, ap_conftree, 0,
+                                             0);
                     }
-                    ap_rputs("<tt>Merge Directory Configs</tt>", r);
-                    comma = 1;
-                }
-                if (modp->create_server_config) {
-                    if (comma) {
-                        ap_rputs(", ", r);
+                    else {
+                        ap_rputs
+                            ("<dt><strong>Module Directives:</strong> <tt>none</tt></dt>",
+                             r);
                     }
-                    ap_rputs("<tt>Create Server Config</tt>", r);
-                    comma = 1;
-                }
-                if (modp->merge_server_config) {
-                    if (comma) {
-                        ap_rputs(", ", r);
+                    more_info = find_more_info(serv, modp->name);
+                    if (more_info) {
+                        ap_rputs
+                            ("<dt><strong>Additional Information:</strong>\n</dt><dd>",
+                             r);
+                        ap_rputs(more_info, r);
+                        ap_rputs("</dd>", r);
                     }
-                    ap_rputs("<tt>Merge Server Configs</tt>", r);
-                    comma = 1;
-                }
-                if (!comma)
-                    ap_rputs("<tt> <em>none</em></tt>", r);
-                comma = 0;
-                ap_rputs("</dt>", r);
-
-                module_request_hook_participate(r, modp);
-
-                cmd = modp->cmds;
-                if (cmd) {
-                    ap_rputs("<dt><strong>Module Directives:</strong></dt>", r);
-                    while (cmd) {
-                        if (cmd->name) {
-                            ap_rputs("<dd><tt>", r);
-                            mod_info_html_cmd_string(r, cmd->name, 0);
-                            ap_rputs(" - <i>", r);
-                            if (cmd->errmsg) {
-                                ap_rputs(cmd->errmsg, r);
-                            }
-                            ap_rputs("</i></tt></dd>\n", r);
-                        }
-                        else {
-                            break;
-                        }
-                        cmd++;
+                    ap_rputs("</dl><hr />\n", r);
+                    if (r->args) {
+                        break;
                     }
-                    ap_rputs("<dt><strong>Current Configuration:</strong></dt>\n", r);
-                    mod_info_module_cmds(r, modp->cmds, ap_conftree);
-                }
-                else {
-                    ap_rputs("<dt><strong>Module Directives:</strong> <tt>none</tt></dt>", r);
-                }
-                more_info = find_more_info(serv, modp->name);
-                if (more_info) {
-                    ap_rputs("<dt><strong>Additional Information:</strong>\n</dt><dd>",
-                          r);
-                    ap_rputs(more_info, r);
-                    ap_rputs("</dd>", r);
-                }
-                ap_rputs("</dl><hr />\n", r);
-                if (r->args) {
-                    break;
                 }
             }
-        }
-        if (!modp && r->args && strcasecmp(r->args, "server")) {
-            ap_rputs("<p><b>No such module</b></p>\n", r);
+            if (!modp && r->args && strcasecmp(r->args, "server")) {
+                ap_rputs("<p><b>No such module</b></p>\n", r);
+            }
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
-    ap_rputs(ap_psignature("",r), r);
+    ap_rputs(ap_psignature("", r), r);
     ap_rputs("</body></html>\n", r);
     /* Done, turn off timeout, close file and return */
     return 0;
 }
 
-static const char *add_module_info(cmd_parms *cmd, void *dummy, 
+static const char *add_module_info(cmd_parms * cmd, void *dummy,
                                    const char *name, const char *info)
 {
     server_rec *s = cmd->server;
-    info_svr_conf *conf = (info_svr_conf *) ap_get_module_config(s->module_config,
-                                                              &info_module);
+    info_svr_conf *conf =
+        (info_svr_conf *) ap_get_module_config(s->module_config,
+                                               &info_module);
     info_entry *new = apr_array_push(conf->more_info);
 
     new->name = name;
     new->info = info;
     return NULL;
 }
 
-static const command_rec info_cmds[] =
-{
+static const command_rec info_cmds[] = {
     AP_INIT_TAKE2("AddModuleInfo", add_module_info, NULL, RSRC_CONF,
                   "a module name and additional information on that module"),
     {NULL}
 };
 
-static void register_hooks(apr_pool_t *p)
+static void register_hooks(apr_pool_t * p)
 {
     ap_hook_handler(display_info, NULL, NULL, APR_HOOK_MIDDLE);
 }
 
-module AP_MODULE_DECLARE_DATA info_module =
-{
+module AP_MODULE_DECLARE_DATA info_module = {
     STANDARD20_MODULE_STUFF,
     NULL,                       /* dir config creater */
     NULL,                       /* dir merger --- default is to override */
     create_info_config,         /* server config */
     merge_info_config,          /* merge server config */
     info_cmds,                  /* command apr_table_t */
