void
Adaptation::Ecap::RequestLineRep::uri(const Area &aUri)
{
    // TODO: if method is not set, URL::parse will assume it is not connect;
    // Can we change URL::parse API to remove the method parameter?
    // TODO: optimize: URL::parse should take constant URL buffer
    char *buf = xstrdup(aUri.toString().c_str());
    const bool ok = theMessage.url.parse(theMessage.method, buf);
    xfree(buf);
    Must(ok);
}