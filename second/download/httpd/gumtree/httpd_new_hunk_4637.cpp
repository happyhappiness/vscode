        return;
    }

    /* If the reneg state is to reject renegotiations, check the SSL
     * state machine and move to ABORT if a Client Hello is being
     * read. */
    if (!scr->is_proxy &&
        (where & SSL_CB_HANDSHAKE_START) &&
        scr->reneg_state == RENEG_REJECT) {
            scr->reneg_state = RENEG_ABORT;
            ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(02042)
                          "rejecting client initiated renegotiation");
    }
    /* If the first handshake is complete, change state to reject any
     * subsequent client-initiated renegotiation. */
    else if ((where & SSL_CB_HANDSHAKE_DONE) && scr->reneg_state == RENEG_INIT) {
        scr->reneg_state = RENEG_REJECT;
    }
