bool
Ssl::Bio::sslFeatures::get(const MemBuf &buf, bool record)
{
    int msgSize;
    if ((msgSize = parseMsgHead(buf)) <= 0) {
        debugs(83, 7, "Not a known SSL handshake message");
        return false;
    }

    if (record) {
        helloMessage.clear();
        helloMessage.append(buf.content(), buf.contentSize());
    }

    const unsigned char *msg = helloRecord(buf);
    if (!msg) {
        debugs(83, 2, "Partial SSL handshake message, can not parse!");
        return false;
    }

    if (msg[0] & 0x80)
        return parseV23Hello(msg, (size_t)msgSize);
    else {
        // Hello messages require 5 bytes header + 1 byte Msg type + 3 bytes for Msg size
        if (buf.contentSize() < 9)
            return false;

        // Check for the Handshake/Message type
        // The type 2 is a ServerHello, the type 1 is a ClientHello
        // RFC5246 section 7.4
        if (msg[5] == 0x2) { // ServerHello message
            if (parseV3ServerHello(msg, (size_t)msgSize)) {
                hasCcsOrNst = checkForCcsOrNst(buf);
                return true;
            }
        } else if (msg[5] == 0x1) // ClientHello message,
            return parseV3Hello(msg, (size_t)msgSize);
    }

    return false;
}