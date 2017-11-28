bool
Ssl::Bio::sslFeatures::checkForCcsOrNst(const MemBuf &buf)
{
    if (helloMsgSize <= 0) //unparsed content?
        return false;

    // Check the records after the Hello record.
    const int afterHello = helloRecordStart + helloMsgSize;
    const unsigned char *msg = reinterpret_cast<const unsigned char *>(buf.content()) + afterHello;
    size_t size = (buf.contentSize() > afterHello) ? (size_t)(buf.contentSize() - afterHello) : 0;
    while (size > 5) {
        const int msgType = msg[0];
        const int msgSslVersion = (msg[1] << 8) | msg[2];
        debugs(83, 7, "SSL Message Version :" << std::hex << std::setw(8) << std::setfill('0') << msgSslVersion);
        // Check for Change Cipher Spec message
        // RFC5246 section 6.2.1
        if (msgType == 0x14) {// Change Cipher Spec message found
            debugs(83, 7, "SSL  Change Cipher Spec message found");
            return true;
        }
        // Check for New Session Ticket message
        // RFC5077 section 3.3
        if (msgType == 0x04) {// New Session Ticket message found
            debugs(83, 7, "TLS  New Session Ticket message found");
            return true;
        }
        // The hello message size exist in 4th and 5th bytes
        size_t msgLength = (msg[3] << 8) + msg[4];
        debugs(83, 7, "SSL Message Size: " << msgLength);
        msgLength += 5;

        if (msgLength <= size) {
            msg += msgLength;
            size -= msgLength;
        } else
            size = 0;
    }
    return false;
}