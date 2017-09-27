        keylen = EVP_PKEY_bits(pkey);
    }

    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                  "handing out built-in DH parameters for %d-bit authenticated connection", keylen);

    if (keylen >= 4096)
        return get_dh4096();
    else if (keylen >= 3072)
        return get_dh3072();
    else if (keylen >= 2048)
        return get_dh2048();
    else
        return get_dh1024();
}

/*
 * This OpenSSL callback function is called when OpenSSL
 * does client authentication and verifies the certificate chain.
 */
