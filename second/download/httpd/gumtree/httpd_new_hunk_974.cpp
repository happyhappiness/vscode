    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Configuring permitted SSL ciphers [%s]", 
                 suite);

    if (!SSL_CTX_set_cipher_list(ctx, MODSSL_PCHAR_CAST suite)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "Unable to configure permitted SSL ciphers");
        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
        ssl_die();
    }
}
