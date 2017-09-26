
    if (MODSSL_TMP_KEY_INIT_DH(s, 512) ||
        MODSSL_TMP_KEY_INIT_DH(s, 1024)) {
        return !OK;
    }

    return OK;
}

/*
 *  Per-module initialization
 */
