                      "stapling_check_response: Error Parsing Response!");
         return SSL_TLSEXT_ERR_OK;
     }
 
     if (!OCSP_resp_find_status(bs, cinf->cid, &status, &reason, &rev,
                                &thisupd, &nextupd)) {
-        /* If ID not present just pass back to client */
+        /* If ID not present pass back to client (if configured so) */
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01935)
                      "stapling_check_response: certificate ID not present in response!");
+        if (mctx->stapling_return_errors == FALSE)
+            rv = SSL_TLSEXT_ERR_NOACK;
     }
     else {
         if (OCSP_check_validity(thisupd, nextupd,
                                 mctx->stapling_resptime_skew,
                                 mctx->stapling_resp_maxage)) {
             if (pok)
