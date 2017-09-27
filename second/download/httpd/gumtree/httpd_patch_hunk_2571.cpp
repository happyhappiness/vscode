                                          SHMCB_DATA(header, subcache),
                                          data_offset, dest_len);
                 dest[dest_len] = '\0';
 
                 rv = iterator(instance, s, userctx, id, idx->id_len,
                               dest, dest_len, pool);
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, s,
+                ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, s, APLOGNO(00855)
                              "shmcb entry iterated");
                 if (rv != APR_SUCCESS)
                     return rv;
             }
             else {
                 /* Already stale, quietly remove and treat as not-found */
                 idx->removed = 1;
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00856)
                              "shmcb_subcache_iterate discarding expired entry");
             }
         }
         /* Increment */
         loop++;
         pos = SHMCB_CYCLIC_INCREMENT(pos, 1, header->index_num);
