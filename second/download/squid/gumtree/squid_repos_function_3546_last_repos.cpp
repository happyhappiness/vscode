bool Adaptation::Icap::ModXact::parseHead(HttpMsg *head)
{
    Must(head);
    debugs(93, 5, "have " << readBuf.length() << " head bytes to parse; state: " << state.parsing);

    Http::StatusCode error = Http::scNone;
    // XXX: performance regression. c_str() data copies
    // XXX: HttpMsg::parse requires a terminated string buffer
    const char *tmpBuf = readBuf.c_str();
    const bool parsed = head->parse(tmpBuf, readBuf.length(), commEof, &error);
    Must(parsed || !error); // success or need more data

    if (!parsed) { // need more data
        debugs(93, 5, HERE << "parse failed, need more data, return false");
        head->reset();
        return false;
    }

    debugs(93, 5, HERE << "parse success, consume " << head->hdr_sz << " bytes, return true");
    readBuf.consume(head->hdr_sz);
    return true;
}