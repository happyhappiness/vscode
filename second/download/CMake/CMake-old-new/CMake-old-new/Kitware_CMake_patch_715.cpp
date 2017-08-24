@@ -46,15 +46,15 @@ int GetWebFile(void)
     proxy_type = 1;
     if (getenv("HTTP_PROXY_PORT") )
       {
-      sprintf("%s:%s", getenv("HTTP_PROXY"), getenv("HTTP_PROXY_PORT"));
+      sprintf(proxy, "%s:%s", getenv("HTTP_PROXY"), getenv("HTTP_PROXY_PORT"));
       }
     else
       {
-      sprintf("%s", getenv("HTTP_PROXY"));
+      sprintf(proxy, "%s", getenv("HTTP_PROXY"));
       }
     if ( getenv("HTTP_PROXY_TYPE") )
       {
-      // HTTP/SOCKS4/SOCKS5
+      /* HTTP/SOCKS4/SOCKS5 */
       if ( strcmp(getenv("HTTP_PROXY_TYPE"), "HTTP") == 0 )
         {
         proxy_type = 1;
@@ -76,7 +76,7 @@ int GetWebFile(void)
     curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
     curl_easy_setopt(curl, CURLOPT_HEADER, 1);
 
-    // Using proxy
+    /* Using proxy */
     if ( proxy_type > 0 )
       {
       curl_easy_setopt(curl, CURLOPT_PROXY, proxy); 