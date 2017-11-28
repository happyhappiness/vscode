void
Adaptation::Ecap::RequestLineRep::method(const Name &aMethod)
{
    if (aMethod.assignedHostId()) {
        const int id = aMethod.hostId();
        Must(METHOD_NONE < id && id < METHOD_ENUM_END);
        Must(id != METHOD_OTHER);
        theMessage.method = HttpRequestMethod(static_cast<_method_t>(id));
    } else {
        const std::string &image = aMethod.image();
        theMessage.method = HttpRequestMethod(image.data(),
                                              image.data() + image.size());
    }
}