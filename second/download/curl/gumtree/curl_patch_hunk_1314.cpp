           ;
         }
         else if(result && global->showerror) {
           fprintf(global->errors, "curl: (%d) %s\n", result, (errorbuffer[0]) ?
                   errorbuffer : curl_easy_strerror(result));
           if(result == CURLE_SSL_CACERT)
-            fprintf(global->errors, "%s%s%s",
-                    CURL_CA_CERT_ERRORMSG1, CURL_CA_CERT_ERRORMSG2,
-                    ((curlinfo->features & CURL_VERSION_HTTPS_PROXY) ?
-                     "HTTPS-proxy has similar options --proxy-cacert "
-                     "and --proxy-insecure.\n" :
-                     ""));
+            fputs(CURL_CA_CERT_ERRORMSG, global->errors);
         }
 
         /* Fall through comment to 'quit_urls' label */
 
         /*
         ** Upon error condition and always that a message has already been
