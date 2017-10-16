           keepit=*end;
           *end=0; /* zero terminate */
           for(i=0; replacements[i].name; i++) {
             if(strequal(ptr, replacements[i].name)) {
               switch(replacements[i].id) {
               case VAR_EFFECTIVE_URL:
-                if(CURLE_OK ==
-                   curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &stringp))
+                if((CURLE_OK ==
+                    curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &stringp))
+                   && stringp)
                   fputs(stringp, stream);
                 break;
               case VAR_HTTP_CODE:
                 if(CURLE_OK ==
                    curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &longinfo))
                   fprintf(stream, "%03d", longinfo);
