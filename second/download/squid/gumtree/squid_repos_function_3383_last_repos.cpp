void
Adaptation::Ecap::HeaderRep::parse(const Area &buf)
{
    Http::StatusCode error;
    Must(theMessage.parse(buf.start, buf.size, true, &error));
}