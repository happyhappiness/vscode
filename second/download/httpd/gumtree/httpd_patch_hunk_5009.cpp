     SSLModConfigRec *mc = myModConfig(s);
 
 #ifdef HAVE_FIPS
 
     if (FIPS_mode() && bits < 1024) {
         mc->pTmpKeys[idx] = NULL;
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01880)
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01880)
                      "Init: Skipping generating temporary "
                      "%d bit DH parameters in FIPS mode", bits);
         return OK;
     }
 
 #endif
