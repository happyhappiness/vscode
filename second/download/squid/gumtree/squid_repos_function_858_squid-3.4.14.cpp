static void
whoisTimeout(const CommTimeoutCbParams &io)
{
    WhoisState *p = static_cast<WhoisState *>(io.data);
    debugs(75, 3, HERE << io.conn << ", URL " << p->entry->url());
    io.conn->close();
}