       if(curlinfo->features & feats[i].bitmask)
         printf("%s ", feats[i].name);
     }
 #ifdef USE_METALINK
     printf("Metalink ");
 #endif
+#ifdef USE_LIBPSL
+    printf("PSL ");
+#endif
     puts(""); /* newline */
   }
 }
 
 void tool_list_engines(CURL *curl)
 {
