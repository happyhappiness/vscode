bool
HttpMsg::parseHeader(Http1::Parser &hp)
{
    // HTTP/1 message contains "zero or more header fields"
    // zero does not need parsing
    // XXX: c_str() reallocates. performance regression.
    if (hp.headerBlockSize() && !header.parse(hp.mimeHeader().c_str(), hp.headerBlockSize())) {
        pstate = psError;
        return false;
    }

    // XXX: we are just parsing HTTP headers, not the whole message prefix here
    hdr_sz = hp.messageHeaderSize();
    pstate = psParsed;
    hdrCacheInit();
    return true;
}