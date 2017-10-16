   if(curl) {
     curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
     /* Do not do the transfer - only connect to host */
     curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);
     res = curl_easy_perform(curl);
 
-    if(CURLE_OK != res) {
-      printf("Error: %s\n", strerror(res));
+    if(res != CURLE_OK) {
+      printf("Error: %s\n", curl_easy_strerror(res));
       return 1;
     }
 
-    /* Extract the socket from the curl handle - we'll need it for waiting.
-     * Note that this API takes a pointer to a 'long' while we use
-     * curl_socket_t for sockets otherwise.
-     */
-    res = curl_easy_getinfo(curl, CURLINFO_LASTSOCKET, &sockextr);
+    /* Extract the socket from the curl handle - we'll need it for waiting. */
+    res = curl_easy_getinfo(curl, CURLINFO_ACTIVESOCKET, &sockfd);
 
-    if(CURLE_OK != res) {
+    if(res != CURLE_OK) {
       printf("Error: %s\n", curl_easy_strerror(res));
       return 1;
     }
 
-    sockfd = (curl_socket_t)sockextr;
+    printf("Sending request.\n");
 
-    /* wait for the socket to become ready for sending */
-    if(!wait_on_socket(sockfd, 0, 60000L)) {
-      printf("Error: timeout.\n");
-      return 1;
-    }
+    do {
+      /* Warning: This example program may loop indefinitely.
+       * A production-quality program must define a timeout and exit this loop
+       * as soon as the timeout has expired. */
+      size_t nsent;
+      do {
+        nsent = 0;
+        res = curl_easy_send(curl, request + nsent_total,
+            request_len - nsent_total, &nsent);
+        nsent_total += nsent;
+
+        if(res == CURLE_AGAIN && !wait_on_socket(sockfd, 0, 60000L)) {
+          printf("Error: timeout.\n");
+          return 1;
+        }
+      } while(res == CURLE_AGAIN);
+
+      if(res != CURLE_OK) {
+        printf("Error: %s\n", curl_easy_strerror(res));
+        return 1;
+      }
 
-    puts("Sending request.");
-    /* Send the request. Real applications should check the iolen
-     * to see if all the request has been sent */
-    res = curl_easy_send(curl, request, strlen(request), &iolen);
+      printf("Sent %" CURL_FORMAT_CURL_OFF_T " bytes.\n",
+        (curl_off_t)nsent);
 
-    if(CURLE_OK != res) {
-      printf("Error: %s\n", curl_easy_strerror(res));
-      return 1;
-    }
-    puts("Reading response.");
+    } while(nsent_total < request_len);
+
+    printf("Reading response.\n");
 
-    /* read the response */
     for(;;) {
+      /* Warning: This example program may loop indefinitely (see above). */
       char buf[1024];
+      size_t nread;
+      do {
+        nread = 0;
+        res = curl_easy_recv(curl, buf, sizeof(buf), &nread);
+
+        if(res == CURLE_AGAIN && !wait_on_socket(sockfd, 1, 60000L)) {
+          printf("Error: timeout.\n");
+          return 1;
+        }
+      } while(res == CURLE_AGAIN);
 
-      wait_on_socket(sockfd, 1, 60000L);
-      res = curl_easy_recv(curl, buf, 1024, &iolen);
-
-      if(CURLE_OK != res)
+      if(res != CURLE_OK) {
+        printf("Error: %s\n", curl_easy_strerror(res));
         break;
+      }
 
-      nread = (curl_off_t)iolen;
+      if(nread == 0) {
+        /* end of the response */
+        break;
+      }
 
-      printf("Received %" CURL_FORMAT_CURL_OFF_T " bytes.\n", nread);
+      printf("Received %" CURL_FORMAT_CURL_OFF_T " bytes.\n",
+        (curl_off_t)nread);
     }
 
     /* always cleanup */
     curl_easy_cleanup(curl);
   }
   return 0;
