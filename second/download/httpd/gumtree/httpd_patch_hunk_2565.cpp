             header->stat_scrolled++;
             /* Loop admin */
             idx = idx2;
             loop++;
         } while (header->subcache_data_size - subcache->data_used < total_len);
 
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00846)
                      "finished force-expire, subcache: idx_used=%d, "
                      "data_used=%d", subcache->idx_used, subcache->data_used);
     }
 
     /* HERE WE ASSUME THAT THE NEW ENTRY SHOULD GO ON THE END! I'M NOT
      * CHECKING WHETHER IT SHOULD BE GENUINELY "INSERTED" SOMEWHERE.
