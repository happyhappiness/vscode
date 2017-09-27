            algoKey |= at;

            /*
             * Log the type of reading
             */
            if (nPassPhraseDialogCur == 0) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, pServ,
                             "unencrypted %s private key - pass phrase not "
                             "required", an);
            }
            else {
                if (cpPassPhraseCur != NULL) {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                                 pServ,
                                 "encrypted %s private key - pass phrase "
                                 "requested", an);
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                                 pServ,
                                 "encrypted %s private key - pass phrase"
                                 " reused", an);
                }
            }

            /*
