                || (strcmp(the_compare_node.value, compare_nodep->value) != 0))
            {
                void *junk;

                junk = util_ald_cache_insert(curl->compare_cache,
                                             &the_compare_node);
                if (junk == NULL) {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "cache_compare: Cache insertion failure.");
                }
            }
            else {
                compare_nodep->lastcompare = curtime;
                compare_nodep->result = result;
            }
