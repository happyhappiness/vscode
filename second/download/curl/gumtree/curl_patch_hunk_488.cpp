 
       if(!toggle)
         /* --no-version yields no output! */
         break;
 
       printf(CURL_ID "%s\n", curl_version());
-      if (curlinfo->protocols) {
+      if(curlinfo->protocols) {
         printf("Protocols: ");
-        for (proto=curlinfo->protocols; *proto; ++proto) {
+        for(proto=curlinfo->protocols; *proto; ++proto) {
           printf("%s ", *proto);
         }
         puts(""); /* newline */
       }
       if(curlinfo->features) {
         unsigned int i;
