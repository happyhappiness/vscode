 {
     unsigned char tempasn[SSL_SESSION_MAX_DER];
     SSL_SESSION *pSession = NULL;
     SHMCBIndex *idx;
     SHMCBHeader *header;
     unsigned int curr_pos, loop, count;
-    unsigned char *ptr;
+    MODSSL_D2I_SSL_SESSION_CONST unsigned char *ptr;
     BOOL to_return = FALSE;
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "entering shmcb_remove_session_id");
 
     /* If there's entries to expire, ditch them first thing. */
