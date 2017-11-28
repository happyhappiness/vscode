bool
Ssl::Bio::sslFeatures::parseV3ServerHello(const unsigned char *messageContainer, size_t messageContainerSize)
{
    // Parse a ServerHello Handshake message
    // RFC5246 section 7.4, 7.4.1.3
    // The ServerHello starts at messageContainer + 5
    const unsigned char *serverHello = messageContainer + 5;

    // The Length field (bytes 1-3) plus 4 bytes of the serverHello message header (1 handshake type + 3 hello length)
    const size_t helloSize = ((serverHello[1] << 16) | (serverHello[2] << 8) | serverHello[3]) + 4;
    debugs(83, 7, "ServerHello message size: " << helloSize);
    if (helloSize > messageContainerSize) {
        debugs(83, 2, "ServerHello parse error");
        return false;
    }

    // helloSize should be at least 38 bytes long:
    // (SSL Version + Random + SessionId Length + Cipher Suite + Compression Method)
    if (helloSize < 38) {
        debugs(83, 2, "Too short ServerHello message");
        return false;
    }

    debugs(83, 7, "Get fake features from v3 ServerHello message.");
    // Get the correct version of the sub-hello message
    sslVersion = (serverHello[4] << 8) | serverHello[5];
    // At the position 38 (HelloHeader (6bytes) + SSL3_RANDOM_SIZE (32bytes))
    const size_t sessIdLen = static_cast<size_t>(serverHello[38]);
    debugs(83, 7, "Session ID Length: " <<  sessIdLen);

    // The size should be enough to hold at least the following
    // 4 (hello header)
    // + 2 (SSL Version) + 32 (random) + 1 (sessionId length)
    // + sessIdLength + 2 (cipher suite) + 1 (compression method)
    // = 42 + sessIdLength
    if (42 + sessIdLen > helloSize) {
        debugs(83, 2, "ciphers length parse error");
        return false;
    }

    // The sessionID stored at 39 position, after sessionID length field
    sessionId.assign(reinterpret_cast<const char *>(serverHello + 39), sessIdLen);

    // Check if there are extensions in hello message
    // RFC5246 section 7.4.1.4
    if (helloSize > 42 + sessIdLen + 2) {
        // 42 + sessIdLen
        const unsigned char *pToExtensions = serverHello + 42 + sessIdLen;
        const size_t extensionsLen = (pToExtensions[0] << 8) | pToExtensions[1];
        // Check if the hello size can hold extensions
        if (42 + 2 + sessIdLen + extensionsLen > helloSize ) {
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
            // SessionTicket TLS Extension, RFC5077 section 3.2
            if (extType == 0x23) {
                tlsTicketsExtension = true;
            }
            ext += extLen;
        }
    }
    return true;
}