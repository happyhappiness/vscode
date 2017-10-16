     free(ci->certinfo); /* free the actual array too */
     ci->certinfo = NULL;
     ci->num_of_certs = 0;
   }
 }
 
-#if defined(USE_SSLEAY) || defined(USE_GNUTLS) || defined(USE_NSS) || \
-    defined(USE_DARWINSSL)
-/* these functions are only used by some SSL backends */
+int Curl_ssl_init_certinfo(struct SessionHandle * data,
+                           int num)
+{
+  struct curl_certinfo * ci = &data->info.certs;
+  struct curl_slist * * table;
+
+  /* Initialize the certificate information structures. Return 0 if OK, else 1.
+   */
+  Curl_ssl_free_certinfo(data);
+  ci->num_of_certs = num;
+  table = calloc((size_t) num, sizeof(struct curl_slist *));
+  if(!table)
+    return 1;
+
+  ci->certinfo = table;
+  return 0;
+}
+
+CURLcode Curl_ssl_push_certinfo_len(struct SessionHandle *data,
+                                    int certnum,
+                                    const char *label,
+                                    const char *value,
+                                    size_t valuelen)
+{
+  struct curl_certinfo * ci = &data->info.certs;
+  char * output;
+  struct curl_slist * nl;
+  CURLcode res = CURLE_OK;
+
+  /* Add an information record for a particular certificate. */
+  output = curl_maprintf("%s:%.*s", label, valuelen, value);
+  if(!output)
+    return CURLE_OUT_OF_MEMORY;
+
+  nl = Curl_slist_append_nodup(ci->certinfo[certnum], output);
+  if(!nl) {
+    free(output);
+    curl_slist_free_all(ci->certinfo[certnum]);
+    res = CURLE_OUT_OF_MEMORY;
+  }
+
+  ci->certinfo[certnum] = nl;
+  return res;
+}
+
+/*
+ * This is a convenience function for push_certinfo_len that takes a zero
+ * terminated value.
+ */
+CURLcode Curl_ssl_push_certinfo(struct SessionHandle *data,
+                                int certnum,
+                                const char *label,
+                                const char *value)
+{
+  size_t valuelen = strlen(value);
+
+  return Curl_ssl_push_certinfo_len(data, certnum, label, value, valuelen);
+}
+
+/* these functions are only provided by some SSL backends */
 
+#ifdef have_curlssl_random
 void Curl_ssl_random(struct SessionHandle *data,
                      unsigned char *entropy,
                      size_t length)
 {
   curlssl_random(data, entropy, length);
 }
+#endif
 
+#ifdef have_curlssl_md5sum
 void Curl_ssl_md5sum(unsigned char *tmp, /* input */
                      size_t tmplen,
                      unsigned char *md5sum, /* output */
                      size_t md5len)
 {
   curlssl_md5sum(tmp, tmplen, md5sum, md5len);
 }
-#endif /* USE_SSLEAY || USE_GNUTLS || USE_NSS || USE_DARWINSSL */
+#endif
 
 #endif /* USE_SSL */
