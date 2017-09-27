                             if (ap_pass_brigade(r->output_filters,
                                                 output_brigade) != APR_SUCCESS) {
                                 ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00887)
                                               "error processing body.%s",
                                               r->connection->aborted ?
                                               " Client aborted connection." : "");
-                                output_failed = 1;
+                                client_failed = 1;
                             }
                             data_sent = 1;
                             apr_brigade_cleanup(output_brigade);
                         }
                     }
                 }
