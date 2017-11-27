 
   status = lcc_listval(connection, &ret_ident, &ret_ident_num);
   if (status != 0) {
     printf("UNKNOWN: %s\n", lcc_strerror(connection));
     if (ret_ident != NULL)
       free(ret_ident);
-    return (RET_UNKNOWN);
+    return RET_UNKNOWN;
   }
 
   status = lcc_sort_identifiers(connection, ret_ident, ret_ident_num);
   if (status != 0) {
     printf("UNKNOWN: %s\n", lcc_strerror(connection));
     if (ret_ident != NULL)
       free(ret_ident);
-    return (RET_UNKNOWN);
+    return RET_UNKNOWN;
   }
 
   for (size_t i = 0; i < ret_ident_num; ++i) {
     char id[1024];
 
     if ((hostname_g != NULL) && (strcasecmp(hostname_g, ret_ident[i].host)))
