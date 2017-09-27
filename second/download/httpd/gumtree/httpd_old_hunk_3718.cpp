                    ldc->reason = "Comparison false (cached)";
                }
                else if (LDAP_NO_SUCH_ATTRIBUTE == compare_nodep->result) {
                    ldc->reason = "Comparison no such attribute (cached)";
                }
                else {
                    ldc->reason = "Comparison undefined (cached)";
                }

                /* record the result code to return with the reason... */
                result = compare_nodep->result;
                /* and unlock this read lock */
                LDAP_CACHE_UNLOCK();
                return result;
            }
        }
        /* unlock this read lock */
        LDAP_CACHE_UNLOCK();
    }
