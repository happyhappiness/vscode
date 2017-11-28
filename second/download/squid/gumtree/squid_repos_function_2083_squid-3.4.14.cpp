void
HttpStateData::writeReplyBody()
{
    truncateVirginBody(); // if needed
    const char *data = readBuf->content();
    int len = readBuf->contentSize();
    addVirginReplyBody(data, len);
    readBuf->consume(len);
}