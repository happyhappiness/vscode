         certs = p7->d.signed_and_enveloped->cert;
         p7->d.signed_and_enveloped->cert = NULL;
         PKCS7_free(p7);
         break;
 
     default:
-        ap_log_error(APLOG_MARK, APLOG_CRIT|APLOG_NOERRNO, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02213)
                      "Don't understand PKCS7 file %s", pkcs7);
         ssl_die();
     }
 
     if (!certs) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT|APLOG_NOERRNO, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02214)
                      "No certificates in %s", pkcs7);
         ssl_die();
     }
 
     fclose(f);
 
