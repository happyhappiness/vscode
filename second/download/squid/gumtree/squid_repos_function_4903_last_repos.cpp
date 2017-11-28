bool
Http::One::Parser::grabMimeBlock(const char *which, const size_t limit)
{
    // MIME headers block exist in (only) HTTP/1.x and ICY
    const bool expectMime = (msgProtocol_.protocol == AnyP::PROTO_HTTP && msgProtocol_.major == 1) ||
                            msgProtocol_.protocol == AnyP::PROTO_ICY ||
                            hackExpectsMime_;

    if (expectMime) {
        /* NOTE: HTTP/0.9 messages do not have a mime header block.
         *       So the rest of the code will need to deal with '0'-byte headers
         *       (ie, none, so don't try parsing em)
         */
        bool containsObsFold;
        if (SBuf::size_type mimeHeaderBytes = headersEnd(buf_, containsObsFold)) {

            // Squid could handle these headers, but admin does not want to
            if (firstLineSize() + mimeHeaderBytes >= limit) {
                debugs(33, 5, "Too large " << which);
                parseStatusCode = Http::scHeaderTooLarge;
                buf_.consume(mimeHeaderBytes);
                parsingStage_ = HTTP_PARSE_DONE;
                return false;
            }

            mimeHeaderBlock_ = buf_.consume(mimeHeaderBytes);
            cleanMimePrefix();
            if (containsObsFold)
                unfoldMime();

            debugs(74, 5, "mime header (0-" << mimeHeaderBytes << ") {" << mimeHeaderBlock_ << "}");

        } else { // headersEnd() == 0
            if (buf_.length()+firstLineSize() >= limit) {
                debugs(33, 5, "Too large " << which);
                parseStatusCode = Http::scHeaderTooLarge;
                parsingStage_ = HTTP_PARSE_DONE;
            } else
                debugs(33, 5, "Incomplete " << which << ", waiting for end of headers");
            return false;
        }

    } else
        debugs(33, 3, "Missing HTTP/1.x identifier");

    // NP: we do not do any further stages here yet so go straight to DONE
    parsingStage_ = HTTP_PARSE_DONE;

    return true;
}