int
Http::One::ResponseParser::parseResponseFirstLine()
{
    Http1::Tokenizer tok(buf_);

    CharacterSet WspDelim = CharacterSet::SP; // strict parse only accepts SP

    if (Config.onoff.relaxed_header_parser) {
        // RFC 7230 section 3.5
        // tolerant parser MAY accept any of SP, HTAB, VT (%x0B), FF (%x0C), or bare CR
        // as whitespace between status-line fields
        WspDelim += CharacterSet::HTAB
                    + CharacterSet("VT,FF","\x0B\x0C")
                    + CharacterSet::CR;
    }

    if (msgProtocol_.protocol != AnyP::PROTO_NONE) {
        debugs(74, 6, "continue incremental parse for " << msgProtocol_);
        debugs(74, DBG_DATA, "parse remaining buf={length=" << tok.remaining().length() << ", data='" << tok.remaining() << "'}");
        // we already found the magic, but not the full line. keep going.
        return parseResponseStatusAndReason(tok, WspDelim);

    } else if (tok.skip(Http1magic)) {
        debugs(74, 6, "found prefix magic " << Http1magic);
        // HTTP Response status-line parse

        // magic contains major version, still need to find minor DIGIT
        int64_t verMinor;
        if (tok.int64(verMinor, 10, false, 1) && tok.skipOne(WspDelim)) {
            msgProtocol_.protocol = AnyP::PROTO_HTTP;
            msgProtocol_.major = 1;
            msgProtocol_.minor = static_cast<unsigned int>(verMinor);

            debugs(74, 6, "found version=" << msgProtocol_);

            debugs(74, DBG_DATA, "parse remaining buf={length=" << tok.remaining().length() << ", data='" << tok.remaining() << "'}");
            buf_ = tok.remaining(); // resume checkpoint
            return parseResponseStatusAndReason(tok, WspDelim);

        } else if (tok.atEnd())
            return 0; // need more to be sure we have it all
        else
            return -1; // invalid version or delimiter, a single SP terminator required

    } else if (tok.skip(IcyMagic)) {
        debugs(74, 6, "found prefix magic " << IcyMagic);
        // ICY Response status-line parse (same as HTTP/1 after the magic version)
        msgProtocol_.protocol = AnyP::PROTO_ICY;
        // NP: ICY has no /major.minor details
        debugs(74, DBG_DATA, "parse remaining buf={length=" << tok.remaining().length() << ", data='" << tok.remaining() << "'}");
        buf_ = tok.remaining(); // resume checkpoint
        return parseResponseStatusAndReason(tok, WspDelim);

    } else if (buf_.length() > Http1magic.length() && buf_.length() > IcyMagic.length()) {
        debugs(74, 2, "unknown/missing prefix magic. Interpreting as HTTP/0.9");
        // found something that looks like an HTTP/0.9 response
        // Gateway/Transform it into HTTP/1.1
        msgProtocol_ = Http::ProtocolVersion(1,1);
        // XXX: probably should use version 0.9 here and upgrade on output,
        // but the old code did 1.1 transformation now.
        statusCode_ = Http::scOkay;
        static const SBuf gatewayPhrase("Gatewaying");
        reasonPhrase_ = gatewayPhrase;
        static const SBuf fakeHttpMimeBlock("X-Transformed-From: HTTP/0.9\r\n"
                                            /* Server: visible_appname_string */
                                            "Mime-Version: 1.0\r\n"
                                            /* Date: squid_curtime */
                                            "Expires: -1\r\n\r\n");
        mimeHeaderBlock_ = fakeHttpMimeBlock;
        parsingStage_ = HTTP_PARSE_DONE;
        return 1; // no more parsing
    }

    return 0; // need more to parse anything.
}