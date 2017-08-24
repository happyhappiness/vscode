@@ -36,7 +36,7 @@ int GetFtpFile(void)
   return retVal;
 }
 
-int GetWebFile(void)
+int GetWebFiles(char *url1, char *url2)
 {
   int retVal = 0;
   CURL *curl;
@@ -98,22 +98,24 @@ int GetWebFile(void)
       }
 
     /* get the first document */
-    curl_easy_setopt(curl, CURLOPT_URL, "http://www.cmake.org/page1.html");
+    curl_easy_setopt(curl, CURLOPT_URL, url1);
     res = curl_easy_perform(curl);
     if ( res != 0 )
       {
-      printf("Error fetching: http://www.cmake.org/page1.html\n");
+      printf("Error fetching: %s\n", url1);
       retVal = 1;
       }
 
     /* get another document from the same server using the same
        connection */
+    /* avoid warnings about url2 since below block is commented out: */
+    (void) url2;
     /*
-      curl_easy_setopt(curl, CURLOPT_URL, "http://www.cmake.org/page2.html");
+      curl_easy_setopt(curl, CURLOPT_URL, url2);
       res = curl_easy_perform(curl);
       if ( res != 0 )
       {
-      printf("Error fetching: http://www.cmake.org/page2.html\n");
+      printf("Error fetching: %s\n", url2);
       retVal = 1;
       }
     */
@@ -130,15 +132,28 @@ int GetWebFile(void)
   return retVal;
 }
 
-int main(/*int argc, char **argv*/)
+
+int main(int argc, char **argv)
 {
   int retVal = 0;
+
   curl_global_init(CURL_GLOBAL_DEFAULT);
-  retVal += GetWebFile();
+
+  if(argc>1)
+    {
+    retVal += GetWebFiles(argv[1], 0);
+    }
+  else
+    {
+    printf("error: first argument should be a url to download\n");
+    retVal = 1;
+    }
 
   /* Do not check the output of FTP socks5 cannot handle FTP yet */
   /* GetFtpFile(); */
   /* do not test ftp right now because we don't enable that port */
+
   curl_global_cleanup();
+
   return retVal;
 }