  * set to ASCII, then send it.
  * @param r   the current request
  * @param ... the strings to write, followed by a NULL pointer
  */
 int ap_rvputs_proto_in_ascii(request_rec *r, ...);
 
-#ifdef __cplusplus
-}
-#endif
-
 #else   /* APR_CHARSET_EBCDIC */
 
 #define ap_xlate_proto_to_ascii(x,y)          /* NOOP */
 #define ap_xlate_proto_from_ascii(x,y)        /* NOOP */
 
 #define ap_rvputs_proto_in_ascii  ap_rvputs
 
 #endif  /* APR_CHARSET_EBCDIC */
-    
+
+#ifdef __cplusplus
+}
+#endif
+
 #endif  /* !APACHE_UTIL_EBCDIC_H */
