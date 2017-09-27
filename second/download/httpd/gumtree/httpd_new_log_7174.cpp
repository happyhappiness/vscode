(!scr->is_proxy &&
        (where & SSL_CB_HANDSHAKE_START) &&
        scr->reneg_state == RENEG_REJECT) {
            scr->reneg_state = RENEG_ABORT;
            ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(02042)
                          "rejecting client initiated renegotiation");
    };