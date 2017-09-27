                              c->client_ip);
             break;
         }
 
         /* Something horribly wrong happened.  Someone didn't block! */
         if (APR_BRIGADE_EMPTY(bb)) {
-            apr_brigade_cleanup(bb);
             ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server, APLOGNO(01612)
                          "ProtocolEcho: Error - read empty brigade from %s!",
                          c->client_ip);
             break;
         }
 
