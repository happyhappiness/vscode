                 if (ap_pass_brigade(r->output_filters,
                                     output_brigade) != APR_SUCCESS) {
                     ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                   "proxy: error processing body");
                     isok = 0;
                 }
+                /* XXX: what about flush here? See mod_jk */
+                data_sent = 1;
                 break;
             default:
                 isok = 0;
                 break;
         }
 
