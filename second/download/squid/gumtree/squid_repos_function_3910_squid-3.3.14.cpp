Adaptation::Ecap::RequestLineRep::Name
Adaptation::Ecap::RequestLineRep::method() const
{
    switch (theMessage.method.id()) {
    case METHOD_GET:
        return libecap::methodGet;
    case METHOD_POST:
        return libecap::methodPost;
    case METHOD_PUT:
        return libecap::methodPut;
    case METHOD_HEAD:
        return libecap::methodHead;
    case METHOD_CONNECT:
        return libecap::methodConnect;
    case METHOD_DELETE:
        return libecap::methodDelete;
    case METHOD_TRACE:
        return libecap::methodTrace;
    default:
        return Name(theMessage.method.image());
    }
}