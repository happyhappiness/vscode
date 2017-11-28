Adaptation::Method
Adaptation::ServiceConfig::parseMethod(const char *str) const
{
    if (!strncasecmp(str, "REQMOD", 6))
        return Adaptation::methodReqmod;

    if (!strncasecmp(str, "RESPMOD", 7))
        return Adaptation::methodRespmod;

    return Adaptation::methodNone;
}