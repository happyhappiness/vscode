void
Adaptation::Ecap::HeaderRep::parse(const Area &buf)
{
    MemBuf mb;
    mb.init();
    mb.append(buf.start, buf.size);
    Http::StatusCode error;
    Must(theMessage.parse(&mb, true, &error));
}