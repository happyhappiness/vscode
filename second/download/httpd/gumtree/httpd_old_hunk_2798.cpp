             * group or we wouldn't be here.
             */
            if (compare_nodep->sgl_processed) {
                if (compare_nodep->subgroupList) {
                    /* Make a local copy of the subgroup list */
                    int i;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "Making local copy of SGL for "
                                  "group (%s)(objectClass=%s) ",
                                  dn, (char *)sgc_ents[base_sgcIndex].name);
                    tmp_local_sgl = apr_pcalloc(r->pool,
                                                sizeof(util_compare_subgroup_t));
                    tmp_local_sgl->len = compare_nodep->subgroupList->len;
