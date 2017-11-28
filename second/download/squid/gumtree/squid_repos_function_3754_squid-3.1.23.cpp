Adaptation::VectPoint
Adaptation::ServiceConfig::parseVectPoint(const char *service_configConfig) const
{
    const char *t = service_configConfig;
    const char *q = strchr(t, '_');

    if (q)
        t = q + 1;

    if (!strcasecmp(t, "precache"))
        return Adaptation::pointPreCache;

    if (!strcasecmp(t, "postcache"))
        return Adaptation::pointPostCache;

    return Adaptation::pointNone;
}