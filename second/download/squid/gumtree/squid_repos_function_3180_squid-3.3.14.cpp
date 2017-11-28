char *
internalLocalUri(const char *dir, const char *name)
{
    return internalRemoteUri(getMyHostname(),
                             getMyPort(), dir, name);
}