        keylen = EVP_PKEY_bits(pkey);
    }

    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                  "handing out built-in DH parameters for %d-bit authenticated connection", keylen);

    return modssl_get_dh_params(keylen);
}

/*
 * This OpenSSL callback function is called when OpenSSL
 * does client authentication and verifies the certificate chain.
 */
