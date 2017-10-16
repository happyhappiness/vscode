                                    service, host);
     maj = gss_import_name(&min, &input_buffer, GSS_C_NT_HOSTBASED_SERVICE,
                           &gssname);
     if(maj != GSS_S_COMPLETE) {
       gss_release_name(&min, &gssname);
       if(service == srv_host) {
-        Curl_failf(data, "Error importing service name %s", input_buffer.value);
+        Curl_failf(data, "Error importing service name %s",
+                   input_buffer.value);
         return AUTH_ERROR;
       }
       service = srv_host;
       continue;
     }
     /* We pass NULL as |output_name_type| to avoid a leak. */
