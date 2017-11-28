void
URL::parseFinish(const AnyP::ProtocolType protocol,
                 const char *const protoStr, // for unknown protocols
                 const char *const aUrlPath,
                 const char *const aHost,
                 const SBuf &aLogin,
                 const int aPort)
{
    setScheme(protocol, protoStr);
    path(aUrlPath);
    host(aHost);
    userInfo(aLogin);
    port(aPort);
}