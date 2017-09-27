     if (status) {
         /* Some parsers are stupid and return an error on blank documents. */
         if (!total_read) {
             *pdoc = NULL;
             return OK;
         }
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00540)
                       "XML parser error (at end). status=%d", status);
         return HTTP_BAD_REQUEST;
     }
 
 #if APR_CHARSET_EBCDIC
     apr_xml_parser_convert_doc(r->pool, *pdoc, ap_hdrs_from_ascii);
 #endif
     return OK;
 
   parser_error:
     (void) apr_xml_parser_geterror(parser, errbuf, sizeof(errbuf));
-    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00541)
                   "XML Parser Error: %s", errbuf);
 
     /* FALLTHRU */
 
   read_error:
     /* make sure the parser is terminated */
