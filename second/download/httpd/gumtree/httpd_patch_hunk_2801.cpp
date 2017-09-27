                     compare_nodep->sgl_processed = 1;
                 }
             }
             else {
                 util_compare_subgroup_t *sgl_copy =
                     util_ald_sgl_dup(curl->compare_cache, tmp_local_sgl);
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01293)
                              "Copying local SGL of len %d for group %s into cache",
                              tmp_local_sgl->len, dn);
                 if (sgl_copy) {
                     if (compare_nodep->subgroupList) {
                         util_ald_sgl_free(curl->compare_cache,
                                           &(compare_nodep->subgroupList));
                     }
                     compare_nodep->subgroupList = sgl_copy;
                     compare_nodep->sgl_processed = 1;
                 }
                 else {
-                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(01294)
                                  "Copy of SGL failed to obtain shared memory, "
                                  "couldn't update cache");
                 }
             }
         }
         LDAP_CACHE_UNLOCK();
