            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02220)
                         "Reconfigured cipher suite will force renegotiation");
        }
    }

    /*
     * override of SSLVerifyClient
     *
     * We force a renegotiation if the reconfigured/new verify type is
     * stronger than the currently active verify type.
     *
     * The order is: none << optional_no_ca << optional << require
