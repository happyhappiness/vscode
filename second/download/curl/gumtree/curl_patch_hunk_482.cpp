         convert_to_network(contp, strlen(contp));
 #endif
         info[i].option = CURLFORM_COPYCONTENTS;
         info[i].value = contp;
         i++;
         info[i].option = CURLFORM_END;
-        if (curl_formadd(httppost, last_post,
-                         CURLFORM_ARRAY, info, CURLFORM_END) != 0) {
+        if(curl_formadd(httppost, last_post,
+                        CURLFORM_ARRAY, info, CURLFORM_END) != 0) {
           warnf(config, "curl_formadd failed!\n");
           free(contents);
           return 7;
         }
       }
     }
