int
Ssl::Bio::sslFeatures::parseMsgHead(const MemBuf &buf)
{
    const unsigned char *head = (const unsigned char *)buf.content();
    const char *s = objToString(head, buf.contentSize());
    debugs(83, 7, "SSL Header: " << s);
    if (buf.contentSize() < 5)
        return 0;

    if (helloMsgSize > 0)
        return helloMsgSize;

    if ((head[0] & 0x80) && head[2] == 0x01 && head[3] == 0x03) {
        debugs(83, 7, "SSL version 2 handshake message with v3 support");
        sslVersion = (head[3] << 8) | head[4];
        helloRecordStart = 0;
        debugs(83, 7, "SSL Version :" << std::hex << std::setw(8) << std::setfill('0') << sslVersion);
        // The hello message size exist in 2nd byte
        helloMsgSize = head[1];
        helloMsgSize +=2;
        initialized_ = true;
        return helloMsgSize;
    }

    const int headSize = buf.contentSize();
    int currentPos = 0;
    do {
        const unsigned char *currentRecord = head + currentPos;
        // Check for Alert Protocol records before hello message. RFC5246 section-7.2
        if (currentRecord[0] == 0x15) {
            int recordSize = (currentRecord[3] << 8) + currentRecord[4];
            // We need at least 5 bytes for each record.
            if ((currentPos + recordSize + 5) > headSize)
                return 0; // Not enough bytes;
            // Check for fatal Alert and abort if found
            if (currentRecord[5] > 1)
                return -1;
            currentPos += recordSize + 5;
        } else if (currentRecord[0] == 0x16) {
            // SSLPlaintext/TLSPlaintext record
            // RFC6101 section 5.2.1, RFC5246 section 6.2.1
            debugs(83, 7, "SSL version 3 handshake message");
            // The SSL version exist in the 2nd and 3rd bytes
            sslVersion = (currentRecord[1] << 8) | currentRecord[2];
            debugs(83, 7, "SSL Version :" << std::hex << std::setw(8) << std::setfill('0') << sslVersion);
            // The hello message size exist in 4th and 5th bytes
            helloMsgSize = (currentRecord[3] << 8) + currentRecord[4];
            debugs(83, 7, "SSL Header Size: " << helloMsgSize);
            helloMsgSize +=5;
            helloRecordStart = currentPos;

            // Set object as initialized. Even if we did not full parsing yet
            // The basic features, like the SSL version is set
            initialized_ = true;
            return helloMsgSize;
        } else {
            debugs(83, 7, "Not an SSL acceptable handshake message (SSLv2 message?)");
            return (helloMsgSize = -1);
        }
    } while (currentPos + 5 <= headSize);

    return 0;
}