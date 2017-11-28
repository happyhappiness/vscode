bool Adaptation::Icap::ModXact::parseHead(HttpMsg *head)
{
    Must(head);
    debugs(93, 5, HERE << "have " << readBuf.contentSize() << " head bytes to parse" <<
           "; state: " << state.parsing);

    Http::StatusCode error = Http::scNone;
    const bool parsed = head->parse(&readBuf, commEof, &error);
    Must(parsed || !error); // success or need more data

    if (!parsed) { // need more data
        debugs(93, 5, HERE << "parse failed, need more data, return false");
        head->reset();
        return false;
    }

    if (HttpRequest *r = dynamic_cast<HttpRequest*>(head))
        urlCanonical(r); // parse does not set HttpRequest::canonical

    debugs(93, 5, HERE << "parse success, consume " << head->hdr_sz << " bytes, return true");
    readBuf.consume(head->hdr_sz);
    return true;
}