bool Adaptation::Icap::Xaction::parseHttpMsg(HttpMsg *msg)
{
    debugs(93, 5, HERE << "have " << readBuf.contentSize() << " head bytes to parse");

    http_status error = HTTP_STATUS_NONE;
    const bool parsed = msg->parse(&readBuf, commEof, &error);
    Must(parsed || !error); // success or need more data

    if (!parsed) {	// need more data
        Must(mayReadMore());
        msg->reset();
        return false;
    }

    readBuf.consume(msg->hdr_sz);
    return true;
}