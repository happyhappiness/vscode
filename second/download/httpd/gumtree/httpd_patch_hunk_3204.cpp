     /* We accept the "extension" string to be converted as
      * a long name (nsComment), short name (DN) or
      * numeric OID (1.2.3.4).
      */
     oid = OBJ_txt2obj(extension, 0);
     if (!oid) {
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(01970)
                       "could not parse OID '%s'", extension);
         ERR_clear_error();
         return NULL;
     }
 
     xs = peer ? SSL_get_peer_certificate(ssl) : SSL_get_certificate(ssl);
