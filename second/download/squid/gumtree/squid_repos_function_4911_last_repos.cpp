bool
Http::One::TeChunkedParser::parseChunkExtension(Http1::Tokenizer &tok, bool skipKnown)
{
    SBuf ext;
    SBuf value;
    while (
        ParseBws(tok) && // Bug 4492: IBM_HTTP_Server sends SP after chunk-size
        tok.skip(';') &&
        ParseBws(tok) && // Bug 4492: ICAP servers send SP before chunk-ext-name
        tok.prefix(ext, CharacterSet::TCHAR)) { // chunk-ext-name

        // whole value part is optional. if no '=' expect next chunk-ext
        if (ParseBws(tok) && tok.skip('=') && ParseBws(tok)) {

            if (!skipKnown) {
                if (ext.cmp("use-original-body",17) == 0 && tok.int64(useOriginBody, 10)) {
                    debugs(94, 3, "Found chunk extension " << ext << "=" << useOriginBody);
                    buf_ = tok.remaining(); // parse checkpoint
                    continue;
                }
            }

            debugs(94, 5, "skipping unknown chunk extension " << ext);

            // unknown might have a value token or quoted-string
            if (tok.quotedStringOrToken(value) && !tok.atEnd()) {
                buf_ = tok.remaining(); // parse checkpoint
                continue;
            }

            // otherwise need more data OR corrupt syntax
            break;
        }

        if (!tok.atEnd())
            buf_ = tok.remaining(); // parse checkpoint (unless there might be more token name)
    }

    if (skipLineTerminator(tok)) {
        buf_ = tok.remaining(); // checkpoint
        // non-0 chunk means data, 0-size means optional Trailer follows
        parsingStage_ = theChunkSize ? Http1::HTTP_PARSE_CHUNK : Http1::HTTP_PARSE_MIME;
        return true;
    }

    return false;
}