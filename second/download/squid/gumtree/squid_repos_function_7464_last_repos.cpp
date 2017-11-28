void
Security::PeerOptions::updateTlsVersionLimits()
{
    if (!tlsMinVersion.isEmpty()) {
        ::Parser::Tokenizer tok(tlsMinVersion);
        int64_t v = 0;
        if (tok.skip('1') && tok.skip('.') && tok.int64(v, 10, false, 1) && v <= 3) {
            // only account for TLS here - SSL versions are handled by options= parameter
            // avoid affecting options= parameter in cachemgr config report
#if USE_OPENSSL
#if SSL_OP_NO_TLSv1
            if (v > 0)
                parsedOptions |= SSL_OP_NO_TLSv1;
#endif
#if SSL_OP_NO_TLSv1_1
            if (v > 1)
                parsedOptions |= SSL_OP_NO_TLSv1_1;
#endif
#if SSL_OP_NO_TLSv1_2
            if (v > 2)
                parsedOptions |= SSL_OP_NO_TLSv1_2;
#endif

#elif USE_GNUTLS
            // XXX: update parsedOptions directly to avoid polluting 'options=' dumps
            SBuf add;
            if (v > 0)
                add.append(":-VERS-TLS1.0");
            if (v > 1)
                add.append(":-VERS-TLS1.1");
            if (v > 2)
                add.append(":-VERS-TLS1.2");

            if (sslOptions.isEmpty())
                add.chop(1); // remove the initial ':'
            sslOptions.append(add);
#endif

        } else {
            debugs(0, DBG_PARSE_NOTE(1), "WARNING: Unknown TLS minimum version: " << tlsMinVersion);
        }

        return;
    }

    if (sslVersion > 2) {
        // backward compatibility hack for sslversion= configuration
        // only use if tls-min-version=N.N is not present
        // values 0-2 for auto and SSLv2 are not supported any longer.
        // Do it this way so we DO cause changes to options= in cachemgr config report
        const char *add = nullptr;
        switch (sslVersion) {
        case 3:
#if USE_OPENSSL
            parsedOptions |= (SSL_OP_NO_TLSv1|SSL_OP_NO_TLSv1_1|SSL_OP_NO_TLSv1_2);
#elif USE_GNUTLS
            add = ":-VERS-TLS1.0:-VERS-TLS1.1:-VERS-TLS1.2";
#endif
            break;
        case 4:
#if USE_OPENSSL
            parsedOptions |= (SSL_OP_NO_SSLv3|SSL_OP_NO_TLSv1_1|SSL_OP_NO_TLSv1_2);
#elif USE_GNUTLS
            add = ":+VERS-TLS1.0:-VERS-TLS1.1:-VERS-TLS1.2";
#endif
            break;
        case 5:
#if USE_OPENSSL
            parsedOptions |= (SSL_OP_NO_SSLv3|SSL_OP_NO_TLSv1|SSL_OP_NO_TLSv1_2);
#elif USE_GNUTLS
            add = ":-VERS-TLS1.0:+VERS-TLS1.1:-VERS-TLS1.2";
#endif
            break;
        case 6:
#if USE_OPENSSL
            parsedOptions |= (SSL_OP_NO_SSLv3|SSL_OP_NO_TLSv1|SSL_OP_NO_TLSv1_1);
#elif USE_GNUTLS
            add = ":-VERS-TLS1.0:-VERS-TLS1.1";
#endif
            break;
        default: // nothing
            break;
        }
        if (add) {
#if USE_GNUTLS // dont bother otherwise
            if (sslOptions.isEmpty())
                sslOptions.append(add+1, strlen(add+1));
            else
                sslOptions.append(add, strlen(add));
#endif
        }
        sslVersion = 0; // prevent sslOptions being repeatedly appended
    }
}