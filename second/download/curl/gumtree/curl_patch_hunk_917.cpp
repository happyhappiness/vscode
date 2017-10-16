       case 'j': /* --ftp-ssl-ccc-mode */
         config->ftp_ssl_ccc = TRUE;
         config->ftp_ssl_ccc_mode = ftpcccmethod(config, nextarg);
         break;
       case 'z': /* --libcurl */
 #ifdef CURL_DISABLE_LIBCURL_OPTION
-        warnf(config,
+        warnf(global,
               "--libcurl option was disabled at build-time!\n");
         return PARAM_OPTION_UNKNOWN;
 #else
         GetStr(&global->libcurl, nextarg);
         break;
 #endif
