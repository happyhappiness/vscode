      * handshake can prevent the timeout from triggering.
      */
     ap_register_input_filter(reqtimeout_filter_name, reqtimeout_filter, NULL,
                              AP_FTYPE_CONNECTION + 8);
 
     /*
+     * We need to pause timeout detection in between requests, for
+     * speculative and non-blocking reads, so between each outgoing EOR
+     * and the next pre_read_request call.
+     */
+    ap_register_output_filter(reqtimeout_filter_name, reqtimeout_eor, NULL,
+                              AP_FTYPE_CONNECTION);
+
+    /*
      * mod_reqtimeout needs to be called before ap_process_http_request (which
      * is run at APR_HOOK_REALLY_LAST) but after all other protocol modules.
      * This ensures that it only influences normal http connections and not
      * e.g. mod_ftp. Also, if mod_reqtimeout used the pre_connection hook, it
      * would be inserted on mod_proxy's backend connections.
      */
