           my_setopt_str(curl, CURLOPT_COOKIEJAR, config->cookiejar);
 
         /* new in libcurl 7.9.7 */
         my_setopt(curl, CURLOPT_COOKIESESSION, config->cookiesession?1L:0L);
 #else
         if(config->cookie || config->cookiefile || config->cookiejar) {
-          warnf(config, "cookie option(s) used even though cookie support "
-                "is disabled!\n");
+          warnf(config->global, "cookie option(s) used even though cookie "
+                "support is disabled!\n");
           return CURLE_NOT_BUILT_IN;
         }
 #endif
 
-        my_setopt_enum(curl, CURLOPT_SSLVERSION, config->ssl_version);
         my_setopt_enum(curl, CURLOPT_TIMECONDITION, (long)config->timecond);
         my_setopt(curl, CURLOPT_TIMEVALUE, (long)config->condtime);
         my_setopt_str(curl, CURLOPT_CUSTOMREQUEST, config->customrequest);
         my_setopt(curl, CURLOPT_STDERR, global->errors);
 
         /* three new ones in libcurl 7.3: */
