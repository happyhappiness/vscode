             goto quit_urls;
           }
           infdopen=TRUE;
           uploadfilesize=fileinfo.st_size;
 
         }
-        else if(uploadfile && curlx_strequal(uploadfile, "-")) {
+        else if(uploadfile && stdin_upload(uploadfile)) {
           SET_BINMODE(stdin);
           infd = STDIN_FILENO;
-          if (curlx_nonblock((curl_socket_t)infd, TRUE) < 0)
-            warnf(config, "fcntl failed on fd=%d: %s\n", infd, strerror(errno));
+          if (curlx_strequal(uploadfile, ".")) {
+            if (curlx_nonblock((curl_socket_t)infd, TRUE) < 0)
+              warnf(config,
+                    "fcntl failed on fd=%d: %s\n", infd, strerror(errno));
+          }
         }
 
         if(uploadfile && config->resume_from_current)
           config->resume_from = -1; /* -1 will then force get-it-yourself */
 
         if(output_expected(url, uploadfile)
