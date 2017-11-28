bool Adaptation::Icap::Xaction::parseHttpMsg(HttpMsg *msg)
{
    debugs(93, 5, "have " << readBuf.length() << " head bytes to parse");

    Http::StatusCode error = Http::scNone;
    // XXX: performance regression c_str() data copies
    const char *buf = readBuf.c_str();
    const bool parsed = msg->parse(buf, readBuf.length(), commEof, &error);
    Must(parsed || !error); // success or need more data

    if (!parsed) {  // need more data
        Must(mayReadMore());
        msg->reset();
        return false;
    }

    readBuf.consume(msg->hdr_sz);
    return true;
}