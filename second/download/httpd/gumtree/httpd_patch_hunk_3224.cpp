             return SSL_TLSEXT_ERR_NOACK;
     }
 
     bs = OCSP_response_get1_basic(rsp);
     if (bs == NULL) {
         /* If we can't parse response just pass it to client */
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01934)
                      "stapling_check_response: Error Parsing Response!");
         return SSL_TLSEXT_ERR_OK;
     }
 
     if (!OCSP_resp_find_status(bs, cinf->cid, &status, &reason, &rev,
                                &thisupd, &nextupd)) {
         /* If ID not present just pass back to client */
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01935)
                      "stapling_check_response: certificate ID not present in response!");
-    } 
+    }
     else {
         if (OCSP_check_validity(thisupd, nextupd,
                                 mctx->stapling_resptime_skew,
                                 mctx->stapling_resp_maxage)) {
             if (pok)
                 *pok = TRUE;
