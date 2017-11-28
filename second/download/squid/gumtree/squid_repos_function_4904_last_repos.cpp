char *
Http::One::Parser::getHeaderField(const char *name)
{
    if (!headerBlockSize() || !name)
        return NULL;

    LOCAL_ARRAY(char, header, GET_HDR_SZ);
    const int namelen = strlen(name);

    debugs(25, 5, "looking for " << name);

    // while we can find more LF in the SBuf
    Http1::Tokenizer tok(mimeHeaderBlock_);
    SBuf p;

    while (tok.prefix(p, LineCharacters())) {
        if (!tok.skipOne(CharacterSet::LF)) // move tokenizer past the LF
            break; // error. reached invalid octet or end of buffer insted of an LF ??

        // header lines must start with the name (case insensitive)
        if (p.substr(0, namelen).caseCmp(name, namelen))
            continue;

        // then a COLON
        if (p[namelen] != ':')
            continue;

        // drop any trailing *CR sequence
        p.trim(Http1::CrLf(), false, true);

        debugs(25, 5, "checking " << p);
        p.consume(namelen + 1);

        // TODO: optimize SBuf::trim to take CharacterSet directly
        Http1::Tokenizer t(p);
        t.skipAll(CharacterSet::WSP);
        p = t.remaining();

        // prevent buffer overrun on char header[];
        p.chop(0, sizeof(header)-1);

        // return the header field-value
        SBufToCstring(header, p);
        debugs(25, 5, "returning " << header);
        return header;
    }

    return NULL;
}