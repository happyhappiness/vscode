const HttpRequest &Adaptation::Icap::ModXact::virginRequest() const
{
    const HttpRequest *request = virgin.cause ?
                                 virgin.cause : dynamic_cast<const HttpRequest*>(virgin.header);
    Must(request);
    return *request;
}