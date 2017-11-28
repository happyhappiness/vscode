{
    MemBuf str;
    char ntoabuf[MAX_IPSTRLEN];

    str.reset();
    /* email subject line */
    str.appendf("CacheErrorInfo - %s", errorPageName(type));
    mb->appendf("?subject=%s", rfc1738_escape_part(str.buf));
    str.reset();
    /* email body */
    str.appendf("CacheHost: %s\r\n", getMyHostname());
    /* - Err Msgs */
    str.appendf("ErrPage: %s\r\n", errorPageName(type));

    if (xerrno) {
        str.appendf("Err: (%d) %s\r\n", xerrno, strerror(xerrno));
    } else {
        str.append("Err: [none]\r\n", 13);
    }
#if USE_AUTH
    if (auth_user_request.getRaw() && auth_user_request->denyMessage())
        str.appendf("Auth ErrMsg: %s\r\n", auth_user_request->denyMessage());
#endif
    if (dnsError.size() > 0)
        str.appendf("DNS ErrMsg: %s\r\n", dnsError.termedBuf());

    /* - TimeStamp */
    str.appendf("TimeStamp: %s\r\n\r\n", mkrfc1123(squid_curtime));

    /* - IP stuff */
    str.appendf("ClientIP: %s\r\n", src_addr.toStr(ntoabuf,MAX_IPSTRLEN));

    if (request && request->hier.host[0] != '\0') {
        str.appendf("ServerIP: %s\r\n", request->hier.host);
    }

    str.append("\r\n", 2);
    /* - HTTP stuff */
    str.append("HTTP Request:\r\n", 15);
    if (request) {
        str.appendf(SQUIDSBUFPH " " SQUIDSBUFPH " %s/%d.%d\n",
                    SQUIDSBUFPRINT(request->method.image()),
                    SQUIDSBUFPRINT(request->url.path()),
                    AnyP::ProtocolType_str[request->http_ver.protocol],
                    request->http_ver.major, request->http_ver.minor);
        request->header.packInto(&str);
    }

    str.append("\r\n", 2);
    /* - FTP stuff */

    if (ftp.request) {
        str.appendf("FTP Request: %s\r\n", ftp.request);
        str.appendf("FTP Reply: %s\r\n", (ftp.reply? ftp.reply:"[none]"));
        str.append("FTP Msg: ", 9);
        wordlistCat(ftp.server_msg, &str);
        str.append("\r\n", 2);
    }

    str.append("\r\n", 2);
    mb->appendf("&body=%s", rfc1738_escape_part(str.buf));
    str.clean();
    return 0;
}

/// \ingroup ErrorPageInternal
#define CVT_BUF_SZ 512
