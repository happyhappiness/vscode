       if(SetHTTPrequest(config,
                         (config->no_body)?HTTPREQ_HEAD:HTTPREQ_GET,
                         &config->httpreq))
         return PARAM_BAD_USE;
       break;
     case 'J': /* --remote-header-name */
-      if (config->include_headers) {
+      if(config->include_headers) {
         warnf(config,
               "--include and --remote-header-name cannot be combined.\n");
         return PARAM_BAD_USE;
       }
       config->content_disposition = toggle;
       break;
