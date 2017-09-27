         return apr_pstrcat(cmd->pool, "Invalid ScriptSock path",
                            arg, NULL);
     }
 
     return NULL;
 }
+static const char *set_script_timeout(cmd_parms *cmd, void *dummy, const char *arg)
+{
+    cgid_dirconf *dc = dummy;
 
+    if (ap_timeout_parameter_parse(arg, &dc->timeout, "s") != APR_SUCCESS) { 
+        return "CGIDScriptTimeout has wrong format";
+    }
+ 
+    return NULL;
+}
 static const command_rec cgid_cmds[] =
 {
     AP_INIT_TAKE1("ScriptLog", set_scriptlog, NULL, RSRC_CONF,
                   "the name of a log for script debugging info"),
     AP_INIT_TAKE1("ScriptLogLength", set_scriptlog_length, NULL, RSRC_CONF,
                   "the maximum length (in bytes) of the script debug log"),
     AP_INIT_TAKE1("ScriptLogBuffer", set_scriptlog_buffer, NULL, RSRC_CONF,
                   "the maximum size (in bytes) to record of a POST request"),
     AP_INIT_TAKE1("ScriptSock", set_script_socket, NULL, RSRC_CONF,
                   "the name of the socket to use for communication with "
                   "the cgi daemon."),
+    AP_INIT_TAKE1("CGIDScriptTimeout", set_script_timeout, NULL, RSRC_CONF | ACCESS_CONF,
+                  "The amount of time to wait between successful reads from "
+                  "the CGI script, in seconds."),
+                  
     {NULL}
 };
 
 static int log_scripterror(request_rec *r, cgid_server_conf * conf, int ret,
                            apr_status_t rv, char *error)
 {
