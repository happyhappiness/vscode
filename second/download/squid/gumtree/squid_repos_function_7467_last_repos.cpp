void
Security::PeerOptions::parseOptions()
{
#if USE_OPENSSL
    ::Parser::Tokenizer tok(sslOptions);
    long op = 0;

    while (!tok.atEnd()) {
        enum {
            MODE_ADD, MODE_REMOVE
        } mode;

        if (tok.skip('-') || tok.skip('!'))
            mode = MODE_REMOVE;
        else {
            (void)tok.skip('+'); // default action is add. ignore if missing operator
            mode = MODE_ADD;
        }

        static const CharacterSet optChars = CharacterSet("TLS-option", "_") + CharacterSet::ALPHA + CharacterSet::DIGIT;
        int64_t hex = 0;
        SBuf option;
        long value = 0;

        // Bug 4429: identify the full option name before determining text or numeric
        if (tok.prefix(option, optChars)) {

            // find the named option in our supported set
            for (struct ssl_option *opttmp = ssl_options; opttmp->name; ++opttmp) {
                if (option.cmp(opttmp->name) == 0) {
                    value = opttmp->value;
                    break;
                }
            }

            // Special case.. hex specification
            ::Parser::Tokenizer tmp(option);
            if (!value && tmp.int64(hex, 16, false) && tmp.atEnd()) {
                value = hex;
            }
        }

        if (value) {
            switch (mode) {
            case MODE_ADD:
                op |= value;
                break;
            case MODE_REMOVE:
                op &= ~value;
                break;
            }
        } else {
            debugs(83, DBG_PARSE_NOTE(1), "ERROR: Unknown TLS option " << option);
        }

        static const CharacterSet delims("TLS-option-delim",":,");
        if (!tok.skipAll(delims) && !tok.atEnd()) {
            fatalf("Unknown TLS option '" SQUIDSBUFPH "'", SQUIDSBUFPRINT(tok.remaining()));
        }

    }

#if SSL_OP_NO_SSLv2
    // compliance with RFC 6176: Prohibiting Secure Sockets Layer (SSL) Version 2.0
    op = op | SSL_OP_NO_SSLv2;
#endif
    parsedOptions = op;

#elif USE_GNUTLS
    if (sslOptions.isEmpty()) {
        parsedOptions.reset();
        return;
    }

    const char *err = nullptr;
    const char *priorities = sslOptions.c_str();
    gnutls_priority_t op;
    if (gnutls_priority_init(&op, priorities, &err) != GNUTLS_E_SUCCESS) {
        fatalf("Unknown TLS option '%s'", err);
    }
    parsedOptions = Security::ParsedOptions(op, [](gnutls_priority_t p) {
        debugs(83, 5, "gnutls_priority_deinit p=" << (void*)p);
        gnutls_priority_deinit(p);
    });
#endif
}