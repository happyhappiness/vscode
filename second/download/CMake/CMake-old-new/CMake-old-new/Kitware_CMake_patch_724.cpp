@@ -16,7 +16,7 @@ int GetFtpFile(void)
     res = curl_easy_perform(curl);
     if ( res != 0 )
       {
-      printf("Error fetching: http://www.cmake.org/\n");
+      printf("Error fetching: ftp://public.kitware.com/pub/cmake/cygwin/setup.hint\n");
       retVal = 1;
       }
 
@@ -43,11 +43,11 @@ int GetWebFile(void)
     curl_easy_setopt(curl, CURLOPT_HEADER, 1);
 
     /* get the first document */
-    curl_easy_setopt(curl, CURLOPT_URL, "http://www.cmake.org/");
+    curl_easy_setopt(curl, CURLOPT_URL, "http://www.cmake.org/HTML/Sponsors.html");
     res = curl_easy_perform(curl);
     if ( res != 0 )
       {
-      printf("Error fetching: http://www.cmake.org/\n");
+      printf("Error fetching: http://www.cmake.org/HTML/Sponsors.html\n");
       retVal = 1;
       }
 