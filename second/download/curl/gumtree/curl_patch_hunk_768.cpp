     return 1;
 
   ci->certinfo = table;
   return 0;
 }
 
+/*
+ * 'value' is NOT a zero terminated string
+ */
 CURLcode Curl_ssl_push_certinfo_len(struct SessionHandle *data,
                                     int certnum,
                                     const char *label,
                                     const char *value,
                                     size_t valuelen)
 {
   struct curl_certinfo * ci = &data->info.certs;
   char * output;
   struct curl_slist * nl;
   CURLcode res = CURLE_OK;
+  size_t labellen = strlen(label);
+  size_t outlen = labellen + 1 + valuelen + 1; /* label:value\0 */
 
-  /* Add an information record for a particular certificate. */
-  output = curl_maprintf("%s:%.*s", label, valuelen, value);
+  output = malloc(outlen);
   if(!output)
     return CURLE_OUT_OF_MEMORY;
 
+  /* sprintf the label and colon */
+  snprintf(output, outlen, "%s:", label);
+
+  /* memcpy the value (it might not be zero terminated) */
+  memcpy(&output[labellen+1], value, valuelen);
+
+  /* zero terminate the output */
+  output[labellen + 1 + valuelen] = 0;
+
   nl = Curl_slist_append_nodup(ci->certinfo[certnum], output);
   if(!nl) {
     free(output);
     curl_slist_free_all(ci->certinfo[certnum]);
     res = CURLE_OUT_OF_MEMORY;
   }
