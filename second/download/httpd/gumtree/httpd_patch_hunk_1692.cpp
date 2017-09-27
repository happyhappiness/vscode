     proxy_hook_canon_handler(proxy_ftp_canon, NULL, NULL, APR_HOOK_MIDDLE);
     /* filters */
     ap_register_output_filter("PROXY_SEND_DIR", proxy_send_dir_filter,
                               NULL, AP_FTYPE_RESOURCE);
 }
 
-module AP_MODULE_DECLARE_DATA proxy_ftp_module = {
+static const command_rec proxy_ftp_cmds[] =
+{
+    AP_INIT_FLAG("ProxyFtpListOnWildcard", set_ftp_list_on_wildcard, NULL,
+     RSRC_CONF|ACCESS_CONF, "Whether wildcard characters in a path cause mod_proxy_ftp to list the files instead of trying to get them. Defaults to on."),
+    AP_INIT_FLAG("ProxyFtpEscapeWildcards", set_ftp_escape_wildcards, NULL,
+     RSRC_CONF|ACCESS_CONF, "Whether the proxy should escape wildcards in paths before sending them to the FTP server.  Defaults to on, but most FTP servers will need it turned off if you need to manage paths that contain wildcard characters."),
+    AP_INIT_TAKE1("ProxyFtpDirCharset", set_ftp_directory_charset, NULL,
+     RSRC_CONF|ACCESS_CONF, "Define the character set for proxied FTP listings"),
+    {NULL}
+};
+
+
+AP_DECLARE_MODULE(proxy_ftp) = {
     STANDARD20_MODULE_STUFF,
-    NULL,                       /* create per-directory config structure */
-    NULL,                       /* merge per-directory config structures */
+    create_proxy_ftp_dir_config,/* create per-directory config structure */
+    merge_proxy_ftp_dir_config, /* merge per-directory config structures */
     NULL,                       /* create per-server config structure */
     NULL,                       /* merge per-server config structures */
-    NULL,                       /* command apr_table_t */
+    proxy_ftp_cmds,             /* command apr_table_t */
     ap_proxy_ftp_register_hook  /* register hooks */
 };
