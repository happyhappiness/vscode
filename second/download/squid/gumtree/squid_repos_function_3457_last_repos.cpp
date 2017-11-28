const libecap::Area
Adaptation::Ecap::XactionRep::usernameValue() const
{
#if USE_AUTH
    const HttpRequest *request = dynamic_cast<const HttpRequest*>(theCauseRep ?
                                 theCauseRep->raw().header : theVirginRep.raw().header);
    Must(request);
    if (request->auth_user_request != NULL) {
        if (char const *name = request->auth_user_request->username())
            return libecap::Area::FromTempBuffer(name, strlen(name));
        else if (request->extacl_user.size() > 0)
            return libecap::Area::FromTempBuffer(request->extacl_user.rawBuf(),
                                                 request->extacl_user.size());
    }
#endif
    return libecap::Area();
}