   conf.beautify = 0;
   g = yajl_gen_alloc(&conf, NULL);
 #endif
 
   if (g == NULL) {
     fprintf(stderr, "Could not allocate JSON generator.\n");
-    return (0);
+    return 0;
   }
 
   if (yajl_gen_map_open(g) != yajl_gen_status_ok)
     goto err;
   if (yajl_gen_string(g, (u_char *)"message", strlen("message")) !=
       yajl_gen_status_ok)
