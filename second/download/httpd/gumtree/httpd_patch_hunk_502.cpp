         return DECLINED;
 
     is_included = !strcmp(r->protocol, "INCLUDED");
 
     p = r->main ? r->main->pool : r->pool;
 
-    if (r->method_number == M_OPTIONS) {
-        /* 99 out of 100 CGI scripts, this is all they support */
-        r->allowed |= (AP_METHOD_BIT << M_GET);
-        r->allowed |= (AP_METHOD_BIT << M_POST);
-        return DECLINED;
-    }
-
     argv0 = apr_filename_of_pathname(r->filename);
     nph = !(strncmp(argv0, "nph-", 4));
     conf = ap_get_module_config(r->server->module_config, &cgi_module);
 
     if (!(ap_allow_options(r) & OPT_EXECCGI) && !is_scriptaliased(r))
         return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
