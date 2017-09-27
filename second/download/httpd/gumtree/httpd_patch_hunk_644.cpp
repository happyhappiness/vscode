                   ap_escape_shell_cmd(r->pool, arg_copy));
     }
 
     return send_parsed_content(f, b);
 }
 
-static void ap_register_include_handler(char *tag, include_handler_fn_t *func)
+static int include_fixup(request_rec *r)
+{
+    include_dir_config *conf;
+
+    conf = ap_get_module_config(r->per_dir_config, &include_module);
+
+    if (r->handler && (strcmp(r->handler, "server-parsed") == 0))
+    {
+        if (!r->content_type || !*r->content_type) {
+            ap_set_content_type(r, "text/html");
+        }
+        r->handler = "default-handler";
+    }
+    else
+#if defined(OS2) || defined(WIN32) || defined(NETWARE)
+    /* These OS's don't support xbithack. This is being worked on. */
+    {
+        return DECLINED;
+    }
+#else
+    {
+        if (conf->xbithack == XBITHACK_OFF) {
+            return DECLINED;
+        }
+
+        if (!(r->finfo.protection & APR_UEXECUTE)) {
+            return DECLINED;
+        }
+
+        if (!r->content_type || strcmp(r->content_type, "text/html")) {
+            return DECLINED;
+        }
+    }
+#endif
+
+    /* We always return declined, because the default handler actually
+     * serves the file.  All we have to do is add the filter.
+     */
+    ap_add_output_filter("INCLUDES", NULL, r, r->connection);
+    return DECLINED;
+}
+
+
+/*
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |                Configuration Handling
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
+
+static void *create_includes_dir_config(apr_pool_t *p, char *dummy)
 {
-    apr_hash_set(include_hash, tag, strlen(tag), (const void *)func);
+    include_dir_config *result = apr_palloc(p, sizeof(include_dir_config));
+
+    result->default_error_msg = DEFAULT_ERROR_MSG;
+    result->default_time_fmt  = DEFAULT_TIME_FORMAT;
+    result->undefined_echo    = DEFAULT_UNDEFINED_ECHO;
+    result->xbithack          = DEFAULT_XBITHACK;
+
+    return result;
 }
 
-static int include_post_config(apr_pool_t *p, apr_pool_t *plog,
-                                apr_pool_t *ptemp, server_rec *s)
+static void *create_includes_server_config(apr_pool_t *p, server_rec *server)
 {
-    include_hash = apr_hash_make(p);
-    
-    ssi_pfn_register = APR_RETRIEVE_OPTIONAL_FN(ap_register_include_handler);
+    include_server_config *result;
 
-    if(ssi_pfn_register) {
-        ssi_pfn_register("if", handle_if);
-        ssi_pfn_register("set", handle_set);
-        ssi_pfn_register("else", handle_else);
-        ssi_pfn_register("elif", handle_elif);
-        ssi_pfn_register("echo", handle_echo);
-        ssi_pfn_register("endif", handle_endif);
-        ssi_pfn_register("fsize", handle_fsize);
-        ssi_pfn_register("config", handle_config);
-        ssi_pfn_register("include", handle_include);
-        ssi_pfn_register("flastmod", handle_flastmod);
-        ssi_pfn_register("printenv", handle_printenv);
-    }
-    return OK;
+    result = apr_palloc(p, sizeof(include_server_config));
+    result->default_end_tag    = DEFAULT_END_SEQUENCE;
+    result->default_start_tag  = DEFAULT_START_SEQUENCE;
+
+    return result;
 }
 
-static const char *set_default_error_msg(cmd_parms *cmd, void *mconfig, const char *msg)
+static const char *set_xbithack(cmd_parms *cmd, void *mconfig, const char *arg)
 {
-    include_dir_config *conf = (include_dir_config *)mconfig;
-    conf->default_error_msg = apr_pstrdup(cmd->pool, msg);
+    include_dir_config *conf = mconfig;
+
+    if (!strcasecmp(arg, "off")) {
+        conf->xbithack = XBITHACK_OFF;
+    }
+    else if (!strcasecmp(arg, "on")) {
+        conf->xbithack = XBITHACK_ON;
+    }
+    else if (!strcasecmp(arg, "full")) {
+        conf->xbithack = XBITHACK_FULL;
+    }
+    else {
+        return "XBitHack must be set to Off, On, or Full";
+    }
+
     return NULL;
 }
 
-static const char *set_default_start_tag(cmd_parms *cmd, void *mconfig, const char *msg)
+static const char *set_default_start_tag(cmd_parms *cmd, void *mconfig,
+                                         const char *tag)
 {
     include_server_config *conf;
+    const char *p = tag;
+
+    /* be consistent. (See below in set_default_end_tag) */
+    while (*p) {
+        if (apr_isspace(*p)) {
+            return "SSIStartTag may not contain any whitespaces";
+        }
+        ++p;
+    }
+
     conf= ap_get_module_config(cmd->server->module_config , &include_module);
-    conf->default_start_tag = apr_pstrdup(cmd->pool, msg);
-    conf->start_tag_len = strlen(conf->default_start_tag );
-    bndm_compile(&conf->start_seq_pat, conf->default_start_tag, 
-                 conf->start_tag_len); 
+    conf->default_start_tag = tag;
 
     return NULL;
 }
-static const char *set_undefined_echo(cmd_parms *cmd, void *mconfig, const char *msg)
+
+static const char *set_default_end_tag(cmd_parms *cmd, void *mconfig,
+                                       const char *tag)
 {
     include_server_config *conf;
-    conf = ap_get_module_config(cmd->server->module_config, &include_module);
-    conf->undefinedEcho = apr_pstrdup(cmd->pool, msg);
-    conf->undefinedEchoLen = strlen(msg);
+    const char *p = tag;
+
+    /* sanity check. The parser may fail otherwise */
+    while (*p) {
+        if (apr_isspace(*p)) {
+            return "SSIEndTag may not contain any whitespaces";
+        }
+        ++p;
+    }
+
+    conf= ap_get_module_config(cmd->server->module_config , &include_module);
+    conf->default_end_tag = tag;
 
     return NULL;
 }
 
+static const char *set_undefined_echo(cmd_parms *cmd, void *mconfig,
+                                      const char *msg)
+{
+    include_dir_config *conf = mconfig;
+    conf->undefined_echo = msg;
+
+    return NULL;
+}
 
-static const char *set_default_end_tag(cmd_parms *cmd, void *mconfig, const char *msg)
+static const char *set_default_error_msg(cmd_parms *cmd, void *mconfig,
+                                         const char *msg)
 {
-    include_server_config *conf;
-    conf= ap_get_module_config(cmd->server->module_config , &include_module);
-    conf->default_end_tag = apr_pstrdup(cmd->pool, msg);
+    include_dir_config *conf = mconfig;
+    conf->default_error_msg = msg;
 
     return NULL;
 }
 
-static const char *set_default_time_fmt(cmd_parms *cmd, void *mconfig, const char *fmt)
+static const char *set_default_time_fmt(cmd_parms *cmd, void *mconfig,
+                                        const char *fmt)
 {
-    include_dir_config *conf = (include_dir_config *)mconfig;
-    conf->default_time_fmt = apr_pstrdup(cmd->pool, fmt);
+    include_dir_config *conf = mconfig;
+    conf->default_time_fmt = fmt;
+
     return NULL;
 }
 
+
 /*
- * Module definition and configuration data structs...
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |        Module Initialization and Configuration
+ * |                                                       |
+ * +-------------------------------------------------------+
  */
+
+static int include_post_config(apr_pool_t *p, apr_pool_t *plog,
+                                apr_pool_t *ptemp, server_rec *s)
+{
+    include_handlers = apr_hash_make(p);
+
+    ssi_pfn_register = APR_RETRIEVE_OPTIONAL_FN(ap_register_include_handler);
+
+    if(ssi_pfn_register) {
+        ssi_pfn_register("if", handle_if);
+        ssi_pfn_register("set", handle_set);
+        ssi_pfn_register("else", handle_else);
+        ssi_pfn_register("elif", handle_elif);
+        ssi_pfn_register("echo", handle_echo);
+        ssi_pfn_register("endif", handle_endif);
+        ssi_pfn_register("fsize", handle_fsize);
+        ssi_pfn_register("config", handle_config);
+        ssi_pfn_register("include", handle_include);
+        ssi_pfn_register("flastmod", handle_flastmod);
+        ssi_pfn_register("printenv", handle_printenv);
+    }
+
+    return OK;
+}
+
 static const command_rec includes_cmds[] =
 {
-    AP_INIT_TAKE1("XBitHack", set_xbithack, NULL, OR_OPTIONS, 
+    AP_INIT_TAKE1("XBitHack", set_xbithack, NULL, OR_OPTIONS,
                   "Off, On, or Full"),
-    AP_INIT_TAKE1("SSIErrorMsg", set_default_error_msg, NULL, OR_ALL, 
+    AP_INIT_TAKE1("SSIErrorMsg", set_default_error_msg, NULL, OR_ALL,
                   "a string"),
     AP_INIT_TAKE1("SSITimeFormat", set_default_time_fmt, NULL, OR_ALL,
                   "a strftime(3) formatted string"),
     AP_INIT_TAKE1("SSIStartTag", set_default_start_tag, NULL, RSRC_CONF,
                   "SSI Start String Tag"),
     AP_INIT_TAKE1("SSIEndTag", set_default_end_tag, NULL, RSRC_CONF,
                   "SSI End String Tag"),
-    AP_INIT_TAKE1("SSIUndefinedEcho", set_undefined_echo, NULL, RSRC_CONF,
-                  "SSI Start String Tag"),
-
+    AP_INIT_TAKE1("SSIUndefinedEcho", set_undefined_echo, NULL, OR_ALL,
+                  "String to be displayed if an echoed variable is undefined"),
     {NULL}
 };
 
-static int include_fixup(request_rec *r)
+static void ap_register_include_handler(char *tag, include_handler_fn_t *func)
 {
-    include_dir_config *conf;
- 
-    conf = (include_dir_config *) ap_get_module_config(r->per_dir_config,
-                                                &include_module);
- 
-    if (r->handler && (strcmp(r->handler, "server-parsed") == 0)) 
-    {
-        if (!r->content_type || !*r->content_type) {
-            ap_set_content_type(r, "text/html");
-        }
-        r->handler = "default-handler";
-    }
-    else 
-#if defined(OS2) || defined(WIN32) || defined(NETWARE)
-    /* These OS's don't support xbithack. This is being worked on. */
-    {
-        return DECLINED;
-    }
-#else
-    {
-        if (*conf->xbithack == xbithack_off) {
-            return DECLINED;
-        }
-
-        if (!(r->finfo.protection & APR_UEXECUTE)) {
-            return DECLINED;
-        }
-
-        if (!r->content_type || strcmp(r->content_type, "text/html")) {
-            return DECLINED;
-        }
-    }
-#endif
-
-    /* We always return declined, because the default handler actually
-     * serves the file.  All we have to do is add the filter.
-     */
-    ap_add_output_filter("INCLUDES", NULL, r, r->connection);
-    return DECLINED;
+    apr_hash_set(include_handlers, tag, strlen(tag), (const void *)func);
 }
 
 static void register_hooks(apr_pool_t *p)
 {
     APR_REGISTER_OPTIONAL_FN(ap_ssi_get_tag_and_value);
     APR_REGISTER_OPTIONAL_FN(ap_ssi_parse_string);
