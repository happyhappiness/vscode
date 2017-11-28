void
Adaptation::Ecap::RequestLineRep::method(const Name &aMethod)
{
    if (aMethod.assignedHostId()) {
        const int id = aMethod.hostId();
        Must(Http::METHOD_NONE < id && id < Http::METHOD_ENUM_END);
        Must(id != Http::METHOD_OTHER);
        theMessage.method = HttpRequestMethod(static_cast<Http::MethodType>(id));
    } else {
        const std::string &image = aMethod.image();
        theMessage.method.HttpRequestMethodXXX(image.c_str());
    }
}