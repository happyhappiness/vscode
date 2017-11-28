Adaptation::Ecap::RequestLineRep::Name
Adaptation::Ecap::RequestLineRep::method() const
{
    switch (theMessage.method.id()) {
    case Http::METHOD_GET:
        return libecap::methodGet;
    case Http::METHOD_POST:
        return libecap::methodPost;
    case Http::METHOD_PUT:
        return libecap::methodPut;
    case Http::METHOD_HEAD:
        return libecap::methodHead;
    case Http::METHOD_CONNECT:
        return libecap::methodConnect;
    case Http::METHOD_DELETE:
        return libecap::methodDelete;
    case Http::METHOD_TRACE:
        return libecap::methodTrace;
    default:
        return Name(theMessage.method.image());
    }
}