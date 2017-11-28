void
Adaptation::Ecap::HeaderRep::parse(const Area &buf)
{
    MemBuf mb;
    mb.init();
    mb.append(buf.start, buf.size);
    http_status error;
    Must(theMessage.parse(&mb, true, &error));
}