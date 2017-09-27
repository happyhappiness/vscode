         cs = NULL;
         dlen = h2_util_base64url_decode(&cs, s, session->pool);
         
         if (APLOGrdebug(session->r)) {
             char buffer[128];
             h2_util_hex_dump(buffer, 128, (char*)cs, dlen);
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, session->r,
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, session->r, APLOGNO(03070)
                           "upgrading h2c session with HTTP2-Settings: %s -> %s (%d)",
                           s, buffer, (int)dlen);
         }
         
         *rv = nghttp2_session_upgrade(session->ngh2, (uint8_t*)cs, dlen, NULL);
         if (*rv != 0) {
