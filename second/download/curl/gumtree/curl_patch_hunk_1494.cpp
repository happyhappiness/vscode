 
       /* new in libcurl 7.7: */
       curl_easy_setopt(curl, CURLOPT_RANDOM_FILE, config->random_file);
       curl_easy_setopt(curl, CURLOPT_EGDSOCKET, config->egd_file);
       curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, config->connecttimeout);
 
-      /* debug */
       if(config->cipher_list)
         curl_easy_setopt(curl, CURLOPT_SSL_CIPHER_LIST, config->cipher_list);
+
+      if(config->httpversion)
+        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, config->httpversion);
+
+      /* new in libcurl 7.9.2: */
+      if(config->disable_epsv)
+        /* disable it */
+        curl_easy_setopt(curl, CURLOPT_FTP_USE_EPSV, FALSE);
+
+      /* new in curl 7.9.7 */
+      if(config->trace_dump) {
+        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
+        curl_easy_setopt(curl, CURLOPT_DEBUGDATA, config);
+        config->conf |= CONF_VERBOSE; /* force verbose */
+      }
+      curl_easy_setopt(curl, CURLOPT_VERBOSE, config->conf&CONF_VERBOSE);
       
       res = curl_easy_perform(curl);
         
+      if((config->progressmode == CURL_PROGRESS_BAR) &&
+         progressbar.calls) {
+        /* if the custom progress bar has been displayed, we output a
+           newline here */
+        fputs("\n", progressbar.out);
+      }
+
       if(config->writeout) {
         ourWriteOut(curl, config->writeout);
       }
+#ifdef USE_ENVIRONMENT
+      if (config->writeenv)
+        ourWriteEnv(curl);
+#endif
 
 #ifdef	VMS
       if (!config->showerror)  {
         vms_show = VMSSTS_HIDE;
       }
 #else
       if((res!=CURLE_OK) && config->showerror)
         fprintf(config->errors, "curl: (%d) %s\n", res, errorbuffer);
 #endif
 
-      if(config->headerfile && !headerfilep && heads.stream)
-        fclose(heads.stream);
-
-      if(urlbuffer)
-        free(urlbuffer);
       if (outfile && !strequal(outfile, "-") && outs.stream)
         fclose(outs.stream);
 
 #ifdef HAVE_UTIME
       /* Important that we set the time _after_ the file has been 
          closed, as is done above here */
