bool
Ssl::Bio::sslFeatures::parseV23Hello(const unsigned char *hello, size_t size)
{
    debugs(83, 7, "Get fake features from v23 ClientHello message.");
    if (size < 7)
        return false;
    //Ciphers list. It is stored after the Session ID.
    const unsigned int ciphersLen = (hello[5] << 8) | hello[6];
    const unsigned char *ciphers = hello + 11;

    if (size < ciphersLen + 11)
        return false;

    if (ciphersLen) {
#if (OPENSSL_VERSION_NUMBER >= 0x10100000L)
        const SSL_METHOD *method = TLS_method();
#else
        const SSL_METHOD *method = SSLv23_method();
#endif
        for (unsigned int i = 0; i < ciphersLen; i += 3) {
            // The v2 hello messages cipher has 3 bytes.
            // The v2 cipher has the first byte not null
            // Because we are going to sent only v3 message we
            // are ignoring these ciphers
            if (ciphers[i] != 0)
                continue;
            const SSL_CIPHER *c = method->get_cipher_by_char((ciphers + i + 1));
            if (c != NULL) {
                if (!clientRequestedCiphers.empty())
                    clientRequestedCiphers.append(":");
                clientRequestedCiphers.append(c->name);
            }
        }
    }
    debugs(83, 7, "Ciphers requested by client: " << clientRequestedCiphers);

    const unsigned int sessionIdLength = (hello[7] << 8) | hello[8];
    debugs(83, 7, "SessionID length: " << sessionIdLength);
    // SessionID starts at: hello+11+ciphersLen
    if (sessionIdLength)
        sessionId.assign((const char *)(hello + 11 + ciphersLen), sessionIdLength);

    const unsigned int challengeLength = (hello[5] << 9) | hello[10];
    debugs(83, 7, "Challenge Length: " << challengeLength);
    //challenge starts at: hello+11+ciphersLen+sessionIdLength

    compressMethod = 0;
    return true;
}