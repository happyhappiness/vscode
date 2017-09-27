     fspec = ap_server_root_relative(cmd->pool, filename);
     if (!fspec) {
 	ap_log_error(APLOG_MARK, APLOG_WARNING, APR_EBADPATH, cmd->server,
 	             "ISAPI: invalid module path, skipping %s", filename);
 	return NULL;
     }
-    if ((rv = apr_stat(&tmp, fspec, APR_FINFO_TYPE, 
-                      cmd->temp_pool)) != APR_SUCCESS) { 
+    if ((rv = apr_stat(&tmp, fspec, APR_FINFO_TYPE,
+                      cmd->temp_pool)) != APR_SUCCESS) {
 	ap_log_error(APLOG_MARK, APLOG_WARNING, rv, cmd->server,
 	    "ISAPI: unable to stat, skipping %s", fspec);
 	return NULL;
     }
     if (tmp.filetype != APR_REG) {
 	ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
 	    "ISAPI: not a regular file, skipping %s", fspec);
 	return NULL;
     }
 
     /* Load the extention as cached (with null request_rec) */
-    rv = isapi_lookup(cmd->pool, cmd->server, NULL, fspec, &isa); 
+    rv = isapi_lookup(cmd->pool, cmd->server, NULL, fspec, &isa);
     if (rv != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_WARNING, rv, cmd->server,
                      "ISAPI: unable to cache, skipping %s", fspec);
 	return NULL;
     }
 
     return NULL;
 }
 
 static const command_rec isapi_cmds[] = {
     AP_INIT_TAKE1("ISAPIReadAheadBuffer", ap_set_int_slot,
-        (void *)APR_OFFSETOF(isapi_dir_conf, read_ahead_buflen), 
+        (void *)APR_OFFSETOF(isapi_dir_conf, read_ahead_buflen),
         OR_FILEINFO, "Maximum client request body to initially pass to the"
                      " ISAPI handler (default: 49152)"),
     AP_INIT_FLAG("ISAPILogNotSupported", ap_set_flag_slot,
-        (void *)APR_OFFSETOF(isapi_dir_conf, log_unsupported), 
+        (void *)APR_OFFSETOF(isapi_dir_conf, log_unsupported),
         OR_FILEINFO, "Log requests not supported by the ISAPI server"
                      " on or off (default: off)"),
     AP_INIT_FLAG("ISAPIAppendLogToErrors", ap_set_flag_slot,
-        (void *)APR_OFFSETOF(isapi_dir_conf, log_to_errlog), 
+        (void *)APR_OFFSETOF(isapi_dir_conf, log_to_errlog),
         OR_FILEINFO, "Send all Append Log requests to the error log"
                      " on or off (default: off)"),
     AP_INIT_FLAG("ISAPIAppendLogToQuery", ap_set_flag_slot,
-        (void *)APR_OFFSETOF(isapi_dir_conf, log_to_query), 
+        (void *)APR_OFFSETOF(isapi_dir_conf, log_to_query),
         OR_FILEINFO, "Append Log requests are concatinated to the query args"
                      " on or off (default: on)"),
     AP_INIT_FLAG("ISAPIFakeAsync", ap_set_flag_slot,
-        (void *)APR_OFFSETOF(isapi_dir_conf, fake_async), 
+        (void *)APR_OFFSETOF(isapi_dir_conf, fake_async),
         OR_FILEINFO, "Fake Asynchronous support for isapi callbacks"
                      " on or off [Experimental] (default: off)"),
-    AP_INIT_ITERATE("ISAPICacheFile", isapi_cmd_cachefile, NULL, 
+    AP_INIT_ITERATE("ISAPICacheFile", isapi_cmd_cachefile, NULL,
         RSRC_CONF, "Cache the specified ISAPI extension in-process"),
     {NULL}
 };
 
 /**********************************************************
  *
