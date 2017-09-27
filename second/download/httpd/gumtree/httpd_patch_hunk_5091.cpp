         }
 
         apr_hash_set(table, key, klen, s);
     }
 
     if (conflict) {
-#ifdef OPENSSL_NO_TLSEXT
+#ifndef HAVE_TLSEXT
         ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server, APLOGNO(01917)
                      "Init: You should not use name-based "
                      "virtual hosts in conjunction with SSL!!");
 #else
         ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server, APLOGNO(02292)
                      "Init: Name-based SSL virtual hosts only "
