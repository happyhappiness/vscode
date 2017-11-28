const libecap::Area
Adaptation::Ecap::XactionRep::clientIpValue() const
{
    const HttpRequest *request = dynamic_cast<const HttpRequest*>(theCauseRep ?
                                 theCauseRep->raw().header : theVirginRep.raw().header);
    Must(request);
    // TODO: move this logic into HttpRequest::clientIp(bool) and
    // HttpRequest::clientIpString(bool) and reuse everywhere
    if (TheConfig.send_client_ip && request) {
        Ip::Address client_addr;
#if FOLLOW_X_FORWARDED_FOR
        if (TheConfig.use_indirect_client) {
            client_addr = request->indirect_client_addr;
        } else
#endif
            client_addr = request->client_addr;
        if (!client_addr.isAnyAddr() && !client_addr.isNoAddr()) {
            char ntoabuf[MAX_IPSTRLEN] = "";
            client_addr.toStr(ntoabuf,MAX_IPSTRLEN);
            return libecap::Area::FromTempBuffer(ntoabuf, strlen(ntoabuf));
        }
    }
    return libecap::Area();
}