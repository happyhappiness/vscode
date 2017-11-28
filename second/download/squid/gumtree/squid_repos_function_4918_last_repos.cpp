int
Http::One::ResponseParser::parseResponseStatusAndReason(Http1::Tokenizer &tok, const CharacterSet &WspDelim)
{
    if (!completedStatus_) {
        debugs(74, 9, "seek status-code in: " << tok.remaining().substr(0,10) << "...");
        /* RFC 7230 section 3.1.2 - status code is 3 DIGIT octets.
         * There is no limit on what those octets may be.
         * 000 through 999 are all valid.
         */
        int64_t statusValue;
        if (tok.int64(statusValue, 10, false, 3) && tok.skipOne(WspDelim)) {

            debugs(74, 6, "found int64 status-code=" << statusValue);
            statusCode_ = static_cast<Http::StatusCode>(statusValue);

            buf_ = tok.remaining(); // resume checkpoint
            completedStatus_ = true;

        } else if (tok.atEnd()) {
            debugs(74, 6, "Parser needs more data");
            return 0; // need more to be sure we have it all

        } else {
            debugs(74, 6, "invalid status-line. invalid code.");
            return -1; // invalid status, a single SP terminator required
        }
        // NOTE: any whitespace after the single SP is part of the reason phrase.
    }

    /* RFC 7230 says we SHOULD ignore the reason phrase content
     * but it has a definite valid vs invalid character set.
     * We interpret the SHOULD as ignoring absence and syntax, but
     * producing an error if it contains an invalid octet.
     */

    debugs(74, 9, "seek reason-phrase in: " << tok.remaining().substr(0,50) << "...");

    // if we got here we are still looking for reason-phrase bytes
    static const CharacterSet phraseChars = CharacterSet::WSP + CharacterSet::VCHAR + CharacterSet::OBSTEXT;
    (void)tok.prefix(reasonPhrase_, phraseChars); // optional, no error if missing
    try {
        if (skipLineTerminator(tok)) {
            debugs(74, DBG_DATA, "parse remaining buf={length=" << tok.remaining().length() << ", data='" << tok.remaining() << "'}");
            buf_ = tok.remaining(); // resume checkpoint
            return 1;
        }
        reasonPhrase_.clear();
        return 0; // need more to be sure we have it all

    } catch (const std::exception &ex) {
        debugs(74, 6, "invalid status-line: " << ex.what());
    }
    return -1;
}