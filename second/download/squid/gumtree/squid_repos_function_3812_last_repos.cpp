int
Ssl::ServerBio::write(const char *buf, int size, BIO *table)
{

    if (holdWrite_) {
        debugs(83, 7, "postpone writing " << size << " bytes to SSL FD " << fd_);
        BIO_set_retry_write(table);
        return -1;
    }

    if (!helloBuild && (bumpMode_ == Ssl::bumpPeek || bumpMode_ == Ssl::bumpStare)) {
        // buf contains OpenSSL-generated ClientHello. We assume it has a
        // complete ClientHello and nothing else, but cannot fully verify
        // that quickly. We only verify that buf starts with a v3+ record
        // containing ClientHello.
        Must(size >= 2); // enough for version and content_type checks below
        Must(buf[1] >= 3); // record's version.major; determines buf[0] meaning
        Must(buf[0] == 22); // TLSPlaintext.content_type == handshake in v3+

        //Hello message is the first message we write to server
        assert(helloMsg.isEmpty());

        if (auto ssl = fd_table[fd_].ssl.get()) {
            if (bumpMode_ == Ssl::bumpPeek) {
                // we should not be here if we failed to parse the client-sent ClientHello
                Must(!clientSentHello.isEmpty());
                if (adjustSSL(ssl, clientTlsDetails, clientSentHello))
                    allowBump = true;
                allowSplice = true;
                // Replace OpenSSL-generated ClientHello with client-sent one.
                helloMsg.append(clientSentHello);
                debugs(83, 7,  "FD " << fd_ << ": Using client-sent ClientHello for peek mode");
            } else { /*Ssl::bumpStare*/
                allowBump = true;
                if (!clientSentHello.isEmpty() && adjustSSL(ssl, clientTlsDetails, clientSentHello)) {
                    allowSplice = true;
                    helloMsg.append(clientSentHello);
                    debugs(83, 7,  "FD " << fd_ << ": Using client-sent ClientHello for stare mode");
                }
            }
        }
        // if we did not use the client-sent ClientHello, then use the OpenSSL-generated one
        if (helloMsg.isEmpty())
            helloMsg.append(buf, size);

        helloBuild = true;
        helloMsgSize = helloMsg.length();
        //allowBump = true;

        if (allowSplice) {
            // Do not write yet.....
            BIO_set_retry_write(table);
            return -1;
        }
    }

    if (!helloMsg.isEmpty()) {
        debugs(83, 7,  "buffered write for FD " << fd_);
        int ret = Ssl::Bio::write(helloMsg.rawContent(), helloMsg.length(), table);
        helloMsg.consume(ret);
        if (!helloMsg.isEmpty()) {
            // We need to retry sendind data.
            // Say to openSSL to retry sending hello message
            BIO_set_retry_write(table);
            return -1;
        }

        // Sending hello message complete. Do not send more data for now...
        holdWrite_ = true;

        // spoof openSSL that we write what it ask us to write
        return size;
    } else
        return Ssl::Bio::write(buf, size, table);
}