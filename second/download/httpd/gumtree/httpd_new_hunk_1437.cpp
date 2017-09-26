
    if (MODSSL_TMP_KEY_INIT_DH(s, 512) ||
        MODSSL_TMP_KEY_INIT_DH(s, 1024)) {
        return !OK;
    }

#ifndef OPENSSL_NO_EC
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "Init: Generating temporary EC parameters (256 bits)");

    if (MODSSL_TMP_KEY_INIT_EC(s, 256)) {
        return !OK;
    }
#endif

    return OK;
}

/*
 *  Per-module initialization
 */
