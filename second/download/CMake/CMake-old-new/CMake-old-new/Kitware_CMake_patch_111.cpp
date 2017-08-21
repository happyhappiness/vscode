@@ -46,7 +46,7 @@ static gss_ctx_id_t gss_context = GSS_C_NO_CONTEXT;
 static int check_gss_err(struct Curl_easy *data,
                          OM_uint32 major_status,
                          OM_uint32 minor_status,
-                         const char* function)
+                         const char *function)
 {
   if(GSS_ERROR(major_status)) {
     OM_uint32 maj_stat, min_stat;
@@ -65,7 +65,7 @@ static int check_gss_err(struct Curl_easy *data,
                                     &msg_ctx, &status_string);
       if(maj_stat == GSS_S_COMPLETE) {
         if(sizeof(buf) > len + status_string.length + 1) {
-          strcpy(buf+len, (char*) status_string.value);
+          strcpy(buf+len, (char *) status_string.value);
           len += status_string.length;
         }
         gss_release_buffer(&min_stat, &status_string);
@@ -86,7 +86,7 @@ static int check_gss_err(struct Curl_easy *data,
                                     &msg_ctx, &status_string);
       if(maj_stat == GSS_S_COMPLETE) {
         if(sizeof(buf) > len + status_string.length)
-          strcpy(buf+len, (char*) status_string.value);
+          strcpy(buf+len, (char *) status_string.value);
         gss_release_buffer(&min_stat, &status_string);
         break;
       }
@@ -123,6 +123,7 @@ CURLcode Curl_SOCKS5_gssapi_negotiate(int sockindex,
   unsigned char socksreq[4]; /* room for GSS-API exchange header only */
   const char *serviceptr = data->set.str[STRING_PROXY_SERVICE_NAME] ?
                            data->set.str[STRING_PROXY_SERVICE_NAME] : "rcmd";
+  const size_t serviceptr_length = strlen(serviceptr);
 
   /*   GSS-API request looks like
    * +----+------+-----+----------------+
@@ -134,22 +135,23 @@ CURLcode Curl_SOCKS5_gssapi_negotiate(int sockindex,
 
   /* prepare service name */
   if(strchr(serviceptr, '/')) {
-    service.value = malloc(strlen(serviceptr));
+    service.length = serviceptr_length;
+    service.value = malloc(service.length);
     if(!service.value)
       return CURLE_OUT_OF_MEMORY;
-    service.length = strlen(serviceptr);
     memcpy(service.value, serviceptr, service.length);
 
     gss_major_status = gss_import_name(&gss_minor_status, &service,
                                        (gss_OID) GSS_C_NULL_OID, &server);
   }
   else {
-    service.value = malloc(strlen(serviceptr) +strlen(conn->proxy.name)+2);
+    service.value = malloc(serviceptr_length +
+                           strlen(conn->socks_proxy.host.name)+2);
     if(!service.value)
       return CURLE_OUT_OF_MEMORY;
-    service.length = strlen(serviceptr) +strlen(conn->proxy.name)+1;
+    service.length = serviceptr_length + strlen(conn->socks_proxy.host.name)+1;
     snprintf(service.value, service.length+1, "%s@%s",
-             serviceptr, conn->proxy.name);
+             serviceptr, conn->socks_proxy.host.name);
 
     gss_major_status = gss_import_name(&gss_minor_status, &service,
                                        GSS_C_NT_HOSTBASED_SERVICE, &server);
@@ -290,9 +292,9 @@ CURLcode Curl_SOCKS5_gssapi_negotiate(int sockindex,
   gss_release_name(&gss_status, &server);
 
   /* Everything is good so far, user was authenticated! */
-  gss_major_status = gss_inquire_context (&gss_minor_status, gss_context,
-                                          &gss_client_name, NULL, NULL, NULL,
-                                          NULL, NULL, NULL);
+  gss_major_status = gss_inquire_context(&gss_minor_status, gss_context,
+                                         &gss_client_name, NULL, NULL, NULL,
+                                         NULL, NULL, NULL);
   if(check_gss_err(data, gss_major_status,
                    gss_minor_status, "gss_inquire_context")) {
     gss_delete_sec_context(&gss_status, &gss_context, NULL);