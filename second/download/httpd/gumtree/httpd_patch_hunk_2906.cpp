     union VALUETYPE p;
     magic_server_config_rec *conf = (magic_server_config_rec *)
                 ap_get_module_config(r->server->module_config, &mime_magic_module);
     struct magic *m;
 
 #if MIME_MAGIC_DEBUG
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01529)
                 MODNAME ": match conf=%x file=%s m=%s m->next=%s last=%s",
                 conf,
                 conf->magicfile ? conf->magicfile : "NULL",
                 conf->magic ? "set" : "NULL",
                 (conf->magic && conf->magic->next) ? "set" : "NULL",
                 conf->last ? "set" : "NULL");
