bool
Ssl::Bio::sslFeatures::parseV3Hello(const unsigned char *messageContainer, size_t messageContainerSize)
{
    // Parse a ClientHello Handshake message
    // RFC5246 section 7.4, 7.4.1.2
    // The ClientHello starts at messageContainer + 5
    const unsigned char * clientHello = messageContainer + 5;

    debugs(83, 7, "Get fake features from v3 ClientHello message.");
    // The Length field (bytes 1-3) plus 4 bytes of the clientHello message header (1 handshake type + 3 hello length)
    const size_t helloSize = ((clientHello[1] << 16) | (clientHello[2] << 8) | clientHello[3]) + 4;
    debugs(83, 7, "ClientHello message size: " << helloSize);
    if (helloSize > messageContainerSize) {
        debugs(83, 2, "ClientHello parse error");
        return false;
    }

    // helloSize should be at least 38 bytes long:
    // (SSL Version(2) + Random(32) + SessionId Length(1) + Cipher Suite Length(2) + Compression Method Length(1))
    if (helloSize < 38) {
        debugs(83, 2, "Too short ClientHello message");
        return false;
    }

    //For SSLv3 or TLSv1.* protocols we can get some more informations
    if (messageContainer[1] != 0x3 || clientHello[0] != 0x1 /*HELLO A message*/) {
        debugs(83, 2, "Not an SSLv3/TLSv1.x client hello message, stop parsing here");
        return true;
    }

    // Get the correct version of the sub-hello message
    sslVersion = (clientHello[4] << 8) | clientHello[5];
    //Get Client Random number. It starts on the position 6 of clientHello message
    memcpy(client_random, clientHello + 6, SSL3_RANDOM_SIZE);
    debugs(83, 7, "Client random: " <<  objToString(client_random, SSL3_RANDOM_SIZE));

    // At the position 38 (6+SSL3_RANDOM_SIZE)
    const size_t sessIDLen = static_cast<size_t>(clientHello[38]);
    debugs(83, 7, "Session ID Length: " <<  sessIDLen);

    // The helloSize should be enough to hold at least the following
    // 1 handshake type + 3 hello Length
    // + 2 (SSL Version) + 32 (random) + 1 (sessionId length)
    // + sessIdLength + 2 (cipher suite length) + 1 (compression method length)
    // = 42 + sessIdLength
    if (42 + sessIDLen > helloSize) {
        debugs(83, 2, "Session ID length parse error");
        return false;
    }

    // The sessionID stored art 39 position, after sessionID length field
    sessionId.assign(reinterpret_cast<const char *>(clientHello + 39), sessIDLen);

    //Ciphers list. It is stored after the Session ID.
    // It is a variable-length vector(RFC5246 section 4.3)
    const unsigned char *ciphers = clientHello + 39 + sessIDLen;
    const size_t ciphersLen = (ciphers[0] << 8) | ciphers[1];
    if (42 + sessIDLen + ciphersLen > helloSize) {
        debugs(83, 2, "ciphers length parse error");
        return false;
    }

    ciphers += 2;
    if (ciphersLen) {
#if (OPENSSL_VERSION_NUMBER >= 0x10100000L)
        const SSL_METHOD *method = TLS_method();
#else
        const SSL_METHOD *method = SSLv23_method();
#endif
        for (size_t i = 0; i < ciphersLen; i += 2) {
            // each cipher in v3/tls  HELLO message is of size 2
            const SSL_CIPHER *c = method->get_cipher_by_char((ciphers + i));
            if (c != NULL) {
                if (!clientRequestedCiphers.empty())
                    clientRequestedCiphers.append(":");
                clientRequestedCiphers.append(c->name);
            } else
                unknownCiphers = true;
        }
    }
    debugs(83, 7, "Ciphers requested by client: " << clientRequestedCiphers);

    // Compression field: 1 bytes the number of compression methods and
    // 1 byte for each compression method
    const unsigned char *compression = ciphers + ciphersLen;
    if (compression[0] > 1)
        compressMethod = 1;
    else
        compressMethod = 0;
    debugs(83, 7, "SSL compression methods number: " << static_cast<int>(compression[0]));

    // Parse Extensions, RFC5246 section 7.4.1.4
    const unsigned char *pToExtensions = compression + 1 + static_cast<int>(compression[0]);
    if ((size_t)((pToExtensions - clientHello) + 2) < helloSize) {
        const size_t extensionsLen = (pToExtensions[0] << 8) | pToExtensions[1];
        if ((pToExtensions - clientHello) + 2 + extensionsLen > helloSize) {
            debugs(83, 2, "Extensions length parse error");
            return false;
        }

        pToExtensions += 2;
        const unsigned char *ext = pToExtensions;
        while (ext + 4 <= pToExtensions + extensionsLen) {
            const size_t extType = (ext[0] << 8) | ext[1];
            ext += 2;
            const size_t extLen = (ext[0] << 8) | ext[1];
            ext += 2;
            debugs(83, 7, "TLS Extension: " << std::hex << extType << " of size:" << extLen);

            if (ext + extLen > pToExtensions + extensionsLen) {
                debugs(83, 2, "Extension " << std::hex << extType << " length parser error");
                return false;
            }

            //The SNI extension has the type 0 (extType == 0)
            // RFC6066 sections 3, 10.2
            // The two first bytes indicates the length of the SNI data (should be extLen-2)
            // The next byte is the hostname type, it should be '0' for normal hostname (ext[2] == 0)
            // The 3rd and 4th bytes are the length of the hostname
            if (extType == 0 && ext[2] == 0) {
                const size_t hostLen = (ext[3] << 8) | ext[4];
                if (hostLen < extLen)
                    serverName.assign(reinterpret_cast<const char *>(ext+5), hostLen);
                debugs(83, 7, "Found server name: " << serverName);
            } else if (extType == 15 && ext[0] != 0) {
                // The heartBeats are the type 15, RFC6520
                doHeartBeats = true;
            } else if (extType == 0x23) {
                //SessionTicket TLS Extension RFC5077
                tlsTicketsExtension = true;
                if (extLen != 0)
                    hasTlsTicket = true;
            } else if (extType == 0x05) {
                // RFC6066 sections 8, 10.2
                tlsStatusRequest = true;
            } else if (extType == 0x3374) {
                // detected TLS next protocol negotiate extension
            } else if (extType == 0x10) {
                // Application-Layer Protocol Negotiation Extension, RFC7301
                const size_t listLen = (ext[0] << 8) | ext[1];
                if (listLen < extLen)
                    tlsAppLayerProtoNeg.assign(reinterpret_cast<const char *>(ext+5), listLen);
            } else
                extensions.push_back(extType);

            ext += extLen;
        }
    }
    return true;
}