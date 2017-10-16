       case 'z': /* --libcurl */
 #ifdef CURL_DISABLE_LIBCURL_OPTION
         warnf(config,
               "--libcurl option was disabled at build-time!\n");
         return PARAM_OPTION_UNKNOWN;
 #else
-        GetStr(&config->libcurl, nextarg);
+        GetStr(&global->libcurl, nextarg);
         break;
 #endif
       case '#': /* --raw */
         config->raw = toggle;
         break;
       case '0': /* --post301 */
