                   capath_from_env?
                   "SSL_CERT_DIR environment variable":"--capath");
           }
           else if(result)
             goto show_error;
         }
-        if(config->proxy_capath)
-          my_setopt_str(curl, CURLOPT_PROXY_CAPATH, config->proxy_capath);
-        else if(config->capath) /* CURLOPT_PROXY_CAPATH default is capath */
-          my_setopt_str(curl, CURLOPT_PROXY_CAPATH, config->capath);
+        /* For the time being if --proxy-capath is not set then we use the
+           --capath value for it, if any. See #1257 */
+        if(config->proxy_capath || config->capath) {
+          result = res_setopt_str(curl, CURLOPT_PROXY_CAPATH,
+                                  (config->proxy_capath ?
+                                   config->proxy_capath :
+                                   config->capath));
+          if(result == CURLE_NOT_BUILT_IN) {
+            if(config->proxy_capath) {
+              warnf(config->global,
+                    "ignoring --proxy-capath, not supported by libcurl\n");
+            }
+          }
+          else if(result)
+            goto show_error;
+        }
 
         if(config->crlfile)
           my_setopt_str(curl, CURLOPT_CRLFILE, config->crlfile);
         if(config->proxy_crlfile)
           my_setopt_str(curl, CURLOPT_PROXY_CRLFILE, config->proxy_crlfile);
         else if(config->crlfile) /* CURLOPT_PROXY_CRLFILE default is crlfile */
