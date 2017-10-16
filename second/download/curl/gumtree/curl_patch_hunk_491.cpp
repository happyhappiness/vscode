                   " involves a big risk of it not working. Use a temporary"
                   " file or a fixed auth type instead!\n");
           }
 
           SET_BINMODE(stdin);
           infd = STDIN_FILENO;
-          if (curlx_strequal(uploadfile, ".")) {
-            if (curlx_nonblock((curl_socket_t)infd, TRUE) < 0)
+          if(curlx_strequal(uploadfile, ".")) {
+            if(curlx_nonblock((curl_socket_t)infd, TRUE) < 0)
               warnf(config,
                     "fcntl failed on fd=%d: %s\n", infd, strerror(errno));
           }
         }
 
         if(uploadfile && config->resume_from_current)
