         break;
       case 'j': /* --ftp-ssl-ccc-mode */
         config->ftp_ssl_ccc = TRUE;
         config->ftp_ssl_ccc_mode = ftpcccmethod(config, nextarg);
         break;
       case 'z': /* --libcurl */
+#ifdef CURL_DISABLE_LIBCURL_OPTION
+        warnf(config,
+              "--libcurl option was disabled at build-time!\n");
+        return PARAM_OPTION_UNKNOWN;
+#else
         GetStr(&config->libcurl, nextarg);
         break;
+#endif
       case '#': /* --raw */
         config->raw = toggle;
         break;
       case '0': /* --post301 */
         config->post301 = toggle;
         break;
