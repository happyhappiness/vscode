               if(effective_url &&
                  curlx_strnequal(effective_url, "http", 4)) {
                 /* This was HTTP(S) */
                 curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);
                 if(response != 200 && response != 206) {
                   metalink_next_res = 1;
-                  fprintf(config->errors,
+                  fprintf(global->errors,
                           "Metalink: fetching (%s) from (%s) FAILED "
                           "(HTTP status code %d)\n",
                           mlfile->filename, this_url, response);
                 }
               }
             }
             else {
               metalink_next_res = 1;
-              fprintf(config->errors,
+              fprintf(global->errors,
                       "Metalink: fetching (%s) from (%s) FAILED (%s)\n",
                       mlfile->filename, this_url,
                       (errorbuffer[0]) ?
                       errorbuffer : curl_easy_strerror((CURLcode)res));
             }
           }
           if(metalink && !metalink_next_res)
-            fprintf(config->errors, "Metalink: fetching (%s) from (%s) OK\n",
+            fprintf(global->errors, "Metalink: fetching (%s) from (%s) OK\n",
                     mlfile->filename, this_url);
 
           /* In all ordinary cases, just break out of loop here */
           break; /* curl_easy_perform loop */
 
         }
 
-        if((config->progressmode == CURL_PROGRESS_BAR) &&
+        if((global->progressmode == CURL_PROGRESS_BAR) &&
            progressbar.calls)
           /* if the custom progress bar has been displayed, we output a
              newline here */
           fputs("\n", progressbar.out);
 
         if(config->writeout)
